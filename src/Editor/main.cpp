#include "Precompiled.h"

#include <unordered_map>

#include <imgui.h>
#include <imgui_internal.h>
#include <GL/gl3w.h> // gl*
#include <GLFW/glfw3.h> // GLFW_KEY*

#include "editor/imgui_editor.h"
#include "editor/history.h"
#include "editor/selection.h"
#include "editor/widget.h"

// imgui 100% 게스트 측을 테스트하려면 이것을 활성화하십시오.
//#define IMGUI_GUEST_ONLY

// 호스트에서 오는 데이터, 대부분 호스트에서 관리하거나 소유하지 않은 것이므로 데이터가 살아 있는지 확인합니다
// (예: imgui 컨텍스트, 다시 로드하는 동안 창을 플릭/재배치하지 않음)
struct HostData {
    int w, h;
    int display_w, display_h;
    ImGuiContext *imgui_context = nullptr;
    void *wndh = nullptr;

    // GLFW input/time data feed to guest
    double timestep = 0.0;
    bool mousePressed[3] = {false, false, false};
    float mouseWheel = 0.0f;
    unsigned short inputCharacters[16 + 1] = {};

    // glfw functions that imgui calls on guest side
    GLFWwindow *window = nullptr;
    const char* (*ImGui_ImplGlfwGL3_GetClipboardText)(void* user_data);
    void(*ImGui_ImplGlfwGL3_SetClipboardText)(void* user_data, const char* text);
    void(*glfwSetCursorPos)(GLFWwindow* handle, double xpos, double ypos);
    void(*glfwGetCursorPos)(GLFWwindow* handle, double* xpos, double* ypos);
    int(*glfwGetWindowAttrib)(GLFWwindow* handle, int attrib);
    int(*glfwGetMouseButton)(GLFWwindow* handle, int button);
    void(*glfwSetInputMode)(GLFWwindow* handle, int mode, int value);
    GLFWcursor* (*glfwCreateStandardCursor)(int shape);
    int (*glfwGetInputMode)(GLFWwindow* handle, int mode);
    void (*glfwSetCursor)(GLFWwindow* windowHandle, GLFWcursor* cursorHandle);
    
    imgui_editor::imgui_editor_context* imgui_editor = nullptr;
    imgui_editor::history* history= nullptr;
    imgui_editor::selection_context* selection= nullptr;

    std::string* root = nullptr;

    bool (*widget_deserialize)(imgui_editor::widget* target, const char* data);
    bool (*open_project)(imgui_editor::imgui_editor_context* ctx, const char* path);

    std::unordered_map<size_t, imgui_editor::widget*>* widgets;
};

static uint32_t     g_failure = 0;
static HostData     *g_data = nullptr; // 호스트에 유지되고 호스트에서 수신된 사용자 데이터를 보유합니다.

// 리로드 사이의 일부 저장된 상태
static auto         CR_STATE g_clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
static unsigned int CR_STATE g_version = 0;

#if defined(IMGUI_GUEST_ONLY)
static ImGuiContext CR_STATE *g_imgui_context = nullptr;
static ImFontAtlas  CR_STATE *g_default_font_atlas = nullptr;
#endif // #if defined(IMGUI_GUEST_ONLY)

// From here on is the imgui sample stuff
// 이제부터 imgui 샘플 자료입니다.
static double       CR_STATE g_Time = 0.0f;
static GLuint       CR_STATE g_FontTexture = 0;
static int          CR_STATE g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
static int          CR_STATE g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;
static int          CR_STATE g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
static unsigned int CR_STATE g_VboHandle = 0, g_VaoHandle = 0, g_ElementsHandle = 0;

// Use if you want to reset your rendering device without losing ImGui state.
// ImGui 상태를 잃지 않고 렌더링 장치를 재설정하려는 경우 사용합니다.
static void ImGui_ImplGlfwGL3_InvalidateDeviceObjects();
static bool ImGui_ImplGlfwGL3_CreateDeviceObjects();

// This is the main rendering function that you have to implement and provide to ImGui (via setting up 'RenderDrawListsFn' in the ImGuiIO structure)
// Note that this implementation is little overcomplicated because we are saving/setting up/restoring every OpenGL state explicitly, in order to be able to run within any OpenGL engine that doesn't do so.
// If text or lines are blurry when integrating ImGui in your engine: in your Render function, try translating your projection matrix by (0.5f,0.5f) or (0.375f,0.375f)
// ImGui에 구현하고 제공해야 하는 주요 렌더링 기능입니다(ImGuiIO 구조에서 'RenderDrawListsFn' 설정을 통해).
// 이 구현은 모든 OpenGL 상태를 명시적으로 저장/설정/복원하므로 그렇게 하지 않는 모든 OpenGL 엔진 내에서 실행될 수 있기 때문에 약간 지나치게 복잡합니다.
// ImGui를 엔진에 통합할 때 텍스트나 선이 흐릿한 경우: Render 기능에서 투영 행렬을 (0.5f,0.5f) 또는 (0.375f,0.375f)로 변환해 보십시오.
static void ImGui_ImplGlfwGL3_RenderDrawLists(ImDrawData* draw_data) 
{
    // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
    // 최소화할 때 렌더링을 피하고 망막 디스플레이의 좌표를 조정합니다(화면 좌표 != 프레임 버퍼 좌표).
    ImGuiIO& io = ImGui::GetIO();
    int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
    int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
    if (fb_width == 0 || fb_height == 0)
        return;
    draw_data->ScaleClipRects(io.DisplayFramebufferScale);

    // Backup GL state
    GLenum last_active_texture; glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint*)&last_active_texture);
    glActiveTexture(GL_TEXTURE0);
    GLint last_program; glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
    GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    GLint last_sampler; glGetIntegerv(GL_SAMPLER_BINDING, &last_sampler);
    GLint last_array_buffer; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
    GLint last_element_array_buffer; glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer);
    GLint last_vertex_array; glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);
    GLint last_polygon_mode[2]; glGetIntegerv(GL_POLYGON_MODE, last_polygon_mode);
    GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
    GLint last_scissor_box[4]; glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
    GLenum last_blend_src_rgb; glGetIntegerv(GL_BLEND_SRC_RGB, (GLint*)&last_blend_src_rgb);
    GLenum last_blend_dst_rgb; glGetIntegerv(GL_BLEND_DST_RGB, (GLint*)&last_blend_dst_rgb);
    GLenum last_blend_src_alpha; glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint*)&last_blend_src_alpha);
    GLenum last_blend_dst_alpha; glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint*)&last_blend_dst_alpha);
    GLenum last_blend_equation_rgb; glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint*)&last_blend_equation_rgb);
    GLenum last_blend_equation_alpha; glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint*)&last_blend_equation_alpha);
    GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
    GLboolean last_enable_cull_face = glIsEnabled(GL_CULL_FACE);
    GLboolean last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
    GLboolean last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST);

    // Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled, polygon fill
    // 렌더 상태 설정: 알파 블렌딩 활성화, 페이스 컬링 없음, 깊이 테스트 없음, 가위 활성화, 다각형 채우기
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Setup viewport, orthographic projection matrix
    glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
    const float ortho_projection[4][4] =
    {
        {2.0f / io.DisplaySize.x, 0.0f,                   0.0f, 0.0f},
        {0.0f,                  2.0f / -io.DisplaySize.y, 0.0f, 0.0f},
        {0.0f,                  0.0f,                  -1.0f, 0.0f},
        {-1.0f,                  1.0f,                   0.0f, 1.0f},
    };
    glUseProgram(g_ShaderHandle);
    glUniform1i(g_AttribLocationTex, 0);
    glUniformMatrix4fv(g_AttribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0]);
    glBindVertexArray(g_VaoHandle);
    glBindSampler(0, 0); // Rely on combined texture/sampler state.

    for (int n = 0; n < draw_data->CmdListsCount; n++) {
        const ImDrawList* cmd_list = draw_data->CmdLists[n];
        const ImDrawIdx* idx_buffer_offset = 0;

        glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.Size * sizeof(ImDrawVert), (const GLvoid*)cmd_list->VtxBuffer.Data, GL_STREAM_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ElementsHandle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx), (const GLvoid*)cmd_list->IdxBuffer.Data, GL_STREAM_DRAW);

        for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
            const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
            if (pcmd->UserCallback) {
                pcmd->UserCallback(cmd_list, pcmd);
            } else {
                glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
                glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
                glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset);
            }
            idx_buffer_offset += pcmd->ElemCount;
        }
    }

    // Restore modified GL state
    glUseProgram(last_program);
    glBindTexture(GL_TEXTURE_2D, last_texture);
    glBindSampler(0, last_sampler);
    glActiveTexture(last_active_texture);
    glBindVertexArray(last_vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer);
    glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
    glBlendFuncSeparate(last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_alpha, last_blend_dst_alpha);
    if (last_enable_blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
    if (last_enable_cull_face) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
    if (last_enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
    if (last_enable_scissor_test) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, last_polygon_mode[0]);
    glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
    glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);
}

static bool ImGui_ImplGlfwGL3_CreateFontsTexture() 
{
    // Build texture atlas
    ImGuiIO& io = ImGui::GetIO();
    unsigned char* pixels;
    int width, height;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);   // Load as RGBA 32-bits (75% of the memory is wasted, but default font is so small) because it is more likely to be compatible with user's existing shaders. If your ImTextureId represent a higher-level concept than just a GL texture id, consider calling GetTexDataAsAlpha8() instead to save on GPU memory.
                                                              // Upload texture to graphics system
    GLint last_texture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    glGenTextures(1, &g_FontTexture);
    glBindTexture(GL_TEXTURE_2D, g_FontTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    // Store our identifier
    io.Fonts->TexID = (void *)(intptr_t)g_FontTexture;

    // Restore state
    glBindTexture(GL_TEXTURE_2D, last_texture);

    return true;
}

static bool ImGui_ImplGlfwGL3_CreateDeviceObjects() 
{
    // Backup GL state
    GLint last_texture, last_array_buffer, last_vertex_array;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);

    const GLchar *vertex_shader =
        "#version 330\n"
        "uniform mat4 ProjMtx;\n"
        "in vec2 Position;\n"
        "in vec2 UV;\n"
        "in vec4 Color;\n"
        "out vec2 Frag_UV;\n"
        "out vec4 Frag_Color;\n"
        "void main()\n"
        "{\n"
        "	Frag_UV = UV;\n"
        "	Frag_Color = Color;\n"
        "	gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
        "}\n";

    const GLchar* fragment_shader =
        "#version 330\n"
        "uniform sampler2D Texture;\n"
        "in vec2 Frag_UV;\n"
        "in vec4 Frag_Color;\n"
        "out vec4 Out_Color;\n"
        "void main()\n"
        "{\n"
        "	Out_Color = Frag_Color * texture( Texture, Frag_UV.st);\n"
        "}\n";

    g_ShaderHandle = glCreateProgram();
    g_VertHandle = glCreateShader(GL_VERTEX_SHADER);
    g_FragHandle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(g_VertHandle, 1, &vertex_shader, 0);
    glShaderSource(g_FragHandle, 1, &fragment_shader, 0);
    glCompileShader(g_VertHandle);
    glCompileShader(g_FragHandle);
    glAttachShader(g_ShaderHandle, g_VertHandle);
    glAttachShader(g_ShaderHandle, g_FragHandle);
    glLinkProgram(g_ShaderHandle);

    g_AttribLocationTex = glGetUniformLocation(g_ShaderHandle, "Texture");
    g_AttribLocationProjMtx = glGetUniformLocation(g_ShaderHandle, "ProjMtx");
    g_AttribLocationPosition = glGetAttribLocation(g_ShaderHandle, "Position");
    g_AttribLocationUV = glGetAttribLocation(g_ShaderHandle, "UV");
    g_AttribLocationColor = glGetAttribLocation(g_ShaderHandle, "Color");

    glGenBuffers(1, &g_VboHandle);
    glGenBuffers(1, &g_ElementsHandle);

    glGenVertexArrays(1, &g_VaoHandle);
    glBindVertexArray(g_VaoHandle);
    glBindBuffer(GL_ARRAY_BUFFER, g_VboHandle);
    glEnableVertexAttribArray(g_AttribLocationPosition);
    glEnableVertexAttribArray(g_AttribLocationUV);
    glEnableVertexAttribArray(g_AttribLocationColor);

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
    glVertexAttribPointer(g_AttribLocationPosition, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, pos));
    glVertexAttribPointer(g_AttribLocationUV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, uv));
    glVertexAttribPointer(g_AttribLocationColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (GLvoid*)OFFSETOF(ImDrawVert, col));
#undef OFFSETOF

    ImGui_ImplGlfwGL3_CreateFontsTexture();

    // Restore modified GL state
    glBindTexture(GL_TEXTURE_2D, last_texture);
    glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
    glBindVertexArray(last_vertex_array);

    return true;
}

static void ImGui_ImplGlfwGL3_InvalidateDeviceObjects() 
{
    if (g_VaoHandle) glDeleteVertexArrays(1, &g_VaoHandle);
    if (g_VboHandle) glDeleteBuffers(1, &g_VboHandle);
    if (g_ElementsHandle) glDeleteBuffers(1, &g_ElementsHandle);
    g_VaoHandle = g_VboHandle = g_ElementsHandle = 0;

    if (g_ShaderHandle && g_VertHandle) glDetachShader(g_ShaderHandle, g_VertHandle);
    if (g_VertHandle) glDeleteShader(g_VertHandle);
    g_VertHandle = 0;

    if (g_ShaderHandle && g_FragHandle) glDetachShader(g_ShaderHandle, g_FragHandle);
    if (g_FragHandle) glDeleteShader(g_FragHandle);
    g_FragHandle = 0;

    if (g_ShaderHandle) glDeleteProgram(g_ShaderHandle);
    g_ShaderHandle = 0;

    if (g_FontTexture) {
        glDeleteTextures(1, &g_FontTexture);
        ImGui::GetIO().Fonts->TexID = 0;
        g_FontTexture = 0;
    }
}

static GLFWwindow* g_Window = nullptr;    // Main window
static GLFWcursor* g_MouseCursors[ImGuiMouseCursor_COUNT] = { 0 };

static void ImGui_ImplGlfw_UpdateMouseCursor()
{
    ImGuiIO& io = ImGui::GetIO();
    if ((io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange) || g_data->glfwGetInputMode(g_Window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
        return;
    ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
    if (imgui_cursor == ImGuiMouseCursor_None || io.MouseDrawCursor)
    {
        // Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
        g_data->glfwSetInputMode(g_Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }
    else
    {
        // Show OS mouse cursor
        // FIXME-PLATFORM: Unfocused windows seems to fail changing the mouse cursor with GLFW 3.2, but 3.3 works here.
        g_data->glfwSetCursor(g_Window, g_MouseCursors[imgui_cursor] ? g_MouseCursors[imgui_cursor] : g_MouseCursors[ImGuiMouseCursor_Arrow]);
        g_data->glfwSetInputMode(g_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

// Some customization to use data from host, call glfw functions
// in the glfw case it is an internal static variable that indicates it
// is already initialized, so we must call glfw functions on the host
// otherwise it will say it is not initialized (true in the dll context).
// 호스트의 데이터를 사용하기 위한 일부 사용자 정의는 glfw의 경우 glfw 함수를 호출하여
// 이미 초기화되었음을 나타내는 내부 정적 변수이므로 호스트에서 glfw 함수를 호출해야 합니다.
// 그렇지 않으면 초기화되지 않았다고 표시됩니다(dll에서 true 문맥).
bool imui_init()
{
    gl3wInit();

#if defined(IMGUI_GUEST_ONLY)
    if (!g_imgui_context) {
        g_imgui_context = new ImGuiContext;
        g_default_font_atlas = new ImFontAtlas;
    }
    ImGui::SetCurrentContext(g_imgui_context);
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts = g_default_font_atlas;
#else

    // This will use the imgui context created in the host side
    // this is needed because imgui has two statics (context and font atlas)
    // also ImVector has destructor that delete its contents, so we cannot
    // rely on imgui internal state, we must manage it.
    // 이것은 호스트 측에서 생성된 imgui 컨텍스트를 사용합니다.
    // imgui에는 두 개의 정적(컨텍스트 및 글꼴 아틀라스)이 있고 ImVector에는 내용을 삭제하는 소멸자가 있으므로
    // imgui 내부 상태에 의존할 수 없으므로 이를 관리해야 하기 때문에 필요합니다.
    ImGui::SetCurrentContext(g_data->imgui_context);
#endif

    g_Window = g_data->window;

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("NotoSansKR-Light.otf", 16.0f, nullptr, io.Fonts->GetGlyphRangesKorean());

    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB; // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    io.SetClipboardTextFn = g_data->ImGui_ImplGlfwGL3_SetClipboardText;
    io.GetClipboardTextFn = g_data->ImGui_ImplGlfwGL3_GetClipboardText;
    io.ClipboardUserData = g_data->window;
    io.ImeWindowHandle = g_data->wndh;

    int windowWidth, windowHeight;
    glfwGetWindowSize(g_data->window, &windowWidth, &windowHeight);

    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(g_data->window, &framebufferWidth, &framebufferHeight);

    float horizontalDPI = framebufferWidth / (windowWidth / 96.0f);
    float verticalDPI = framebufferHeight / (windowHeight / 96.0f);

    g_MouseCursors[ImGuiMouseCursor_Arrow] = g_data->glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_TextInput] = g_data->glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_ResizeNS] = g_data->glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_ResizeEW] = g_data->glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_Hand] = g_data->glfwCreateStandardCursor(GLFW_HAND_CURSOR);

#if GLFW_HAS_NEW_CURSORS // 3.4
    g_MouseCursors[ImGuiMouseCursor_ResizeAll] = g_data->glfwCreateStandardCursor(GLFW_RESIZE_ALL_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_ResizeNESW] = g_data->glfwCreateStandardCursor(GLFW_RESIZE_NESW_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = g_data->glfwCreateStandardCursor(GLFW_RESIZE_NWSE_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_NotAllowed] = g_data->glfwCreateStandardCursor(GLFW_NOT_ALLOWED_CURSOR);
#else
    g_MouseCursors[ImGuiMouseCursor_ResizeAll] = g_data->glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_ResizeNESW] = g_data->glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_ResizeNWSE] = g_data->glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    g_MouseCursors[ImGuiMouseCursor_NotAllowed] = g_data->glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
#endif

    return true;
}

static void imui_shutdown() 
{
    for (ImGuiMouseCursor cursor_n = 0; cursor_n < ImGuiMouseCursor_COUNT; cursor_n++)
    {
        glfwDestroyCursor(g_MouseCursors[cursor_n]);
        g_MouseCursors[cursor_n] = NULL;
    }

    ImGui_ImplGlfwGL3_InvalidateDeviceObjects();
#if !defined(IMGUI_GUEST_ONLY)
    ImGui::Shutdown();
    ImGui::DestroyContext(g_data->imgui_context);
#else
    ImGui::Shutdown(g_imgui_context);

    // Trying to get imgui to be 100% in guest context, not working right now.
    // imgui가 게스트 컨텍스트에서 100%가 되도록 하려고 하지만 지금은 작동하지 않습니다.
    delete g_default_font_atlas;
    g_default_font_atlas = nullptr;

    delete g_imgui_context;
    g_imgui_context = nullptr;
#endif
}

static void imui_frame_end() 
{
    glViewport(0, 0, g_data->display_w, g_data->display_h);
    glClearColor(g_clear_color.x, g_clear_color.y, g_clear_color.z, g_clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawLists(ImGui::GetDrawData());
}

static void imui_frame_begin() 
{
    if (!g_FontTexture)
        ImGui_ImplGlfwGL3_CreateDeviceObjects();
    
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    // Proxy things from glfw to imgui
    // glfw에서 imgui로 프록시 작업
    for (int i = 0; g_data->inputCharacters[i]; ++i) {
        io.AddInputCharacter(g_data->inputCharacters[i]);
    }

    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

    // Setup display size (every frame to accommodate for window resizing)
    int w = g_data->w;
    int h = g_data->h;
    int display_w = g_data->display_w;
    int display_h = g_data->display_h;
    io.DisplaySize = ImVec2((float)w, (float)h);
    io.DisplayFramebufferScale = ImVec2(w > 0 ? ((float)display_w / w) : 0, h > 0 ? ((float)display_h / h) : 0);

    double current_time = g_data->timestep;
    io.DeltaTime = g_Time > 0.0 ? (float)(current_time - g_Time) : (float)(1.0f / 60.0f);
    g_Time = current_time;

    // Setup inputs
    // (we already got mouse wheel, keyboard keys & characters from glfw callbacks polled in glfwPollEvents())
    if (g_data->glfwGetWindowAttrib(g_data->window, GLFW_FOCUSED)) {
        if (io.WantSetMousePos) {
            g_data->glfwSetCursorPos(g_data->window, (double)io.MousePos.x, (double)io.MousePos.y);   // Set mouse position if requested by io.WantMoveMouse flag (used when io.NavMovesTrue is enabled by user and using directional navigation)
        } else {
            double mouse_x, mouse_y;
            g_data->glfwGetCursorPos(g_data->window, &mouse_x, &mouse_y);
            io.MousePos = ImVec2((float)mouse_x, (float)mouse_y);   // Get mouse position in screen coordinates (set to -1,-1 if no mouse / on another screen, etc.)
        }
    }

    for (int i = 0; i < 3; i++) {
        io.MouseDown[i] = g_data->mousePressed[i] || g_data->glfwGetMouseButton(g_data->window, i) != 0;    // If a mouse press event came, always pass it as "mouse held this frame", so we don't miss click-release events that are shorter than 1 frame.
        g_data->mousePressed[i] = false;
    }

    io.MouseWheel = g_data->mouseWheel;
    g_data->mouseWheel = 0.0f;
    // Hide OS mouse cursor if ImGui is drawing it
    g_data->glfwSetInputMode(g_data->window, GLFW_CURSOR, io.MouseDrawCursor ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);

    ImGui_ImplGlfw_UpdateMouseCursor();

    // Start the frame
    ImGui::NewFrame();
}

static void test_crash() 
{
    ImGui::EndFrame();
    int *addr = NULL; (void)addr; // warning
    int i = *addr;
    (void)i;
}

namespace imgui_editor
{
    std::unordered_map<size_t, widget*>* g_widget_table = nullptr;
}

CR_EXPORT int cr_main(cr_plugin *ctx, cr_op operation) 
{
    assert(ctx);
    g_data = (HostData *)ctx->userdata;
    g_version = ctx->version;
    g_failure = ctx->failure;
    
    switch (operation) {
        case CR_LOAD:
            imui_init();
            imgui_editor::g_widget_table = g_data->widgets;
            initialize_editor(g_data->imgui_editor, g_data->root->c_str());
            init_history(g_data->history);
            init_selection(g_data->selection);

			g_data->widget_deserialize = imgui_editor::widget_deserialize;
			g_data->open_project = imgui_editor::open_project;

            return 0;

        case CR_UNLOAD:
            // if needed, save stuff to pass over to next instance
            // 필요한 경우 다음 인스턴스로 전달할 항목을 저장합니다.
            *g_data->root = widget_serialize(g_data->imgui_editor->root);
            finalize_history(g_data->history);
            if (g_FontTexture) {
                glDeleteTextures(1, &g_FontTexture);
                ImGui::GetIO().Fonts->TexID = 0;
                g_FontTexture = 0;
            }
            return 0;

        case CR_CLOSE:
            imui_shutdown();
            return 0;
            
        case CR_STEP:
            imui_frame_begin();
            imgui_editor::draw_editor_context(g_data->imgui_editor, g_data->history);
            imui_frame_end();
            return 0;
    }

    return 0;
}

