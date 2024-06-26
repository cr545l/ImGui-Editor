#include <fstream>
#include <vector>
#include <unordered_map>

#include <imgui.h>
#include <imgui_internal.h>
#include <GLFW/glfw3.h>
#ifdef _WIN32
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>
#endif
#define CR_HOST CR_UNSAFE
#include <CR/cr.h>

#include <simpleini/SimpleIni.h>

#include "Precompiled.h"

#include "editor/history.h"
#include "editor/selection.h"
#include "editor/imgui_editor.h"

const char* plugin = DEPLOY_PATH "/" CR_PLUGIN("editor");

// This HostData has too much stuff for the sample mostly because
// glfw and imgui have static global state.
// For glfw the issue is a flag "initialized", so anything glfw that
// we call linked into guest will be "not initialized".
// imgui has some trouble with ImVector destructor that requires quite a lot
// of boilerplate to workaround it.

// 이 HostData에는 샘플에 대한 내용이 너무 많습니다. 대부분 glfw 및 imgui에 정적 전역 상태가 있기 때문입니다.
// glfw의 경우 문제는 "초기화" 플래그이므로 guest에 연결된 glfw는 "초기화되지 않음"입니다.
// imgui는 문제를 해결하기 위해 많은 상용구가 필요한 ImVector 소멸자에 문제가 있습니다.

struct HostData
{
    int w, h;
	float high_dpi_factor;
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
    void(*glfwSetCursorPosInvoke)(GLFWwindow* handle, double xpos, double ypos);
    void(*glfwGetCursorPosInvoke)(GLFWwindow* handle, double* xpos, double* ypos);
    int(*glfwGetWindowAttribInvoke)(GLFWwindow* handle, int attrib);
    int(*glfwGetMouseButtonInvoke)(GLFWwindow* handle, int button);
    void(*glfwSetInputModeInvoke)(GLFWwindow* handle, int mode, int value);
    GLFWcursor* (*glfwCreateStandardCursorInvoke)(int shape);
    int (*glfwGetInputModeInvoke)(GLFWwindow* handle, int mode);
    void (*glfwSetCursorInvoke)(GLFWwindow* windowHandle, GLFWcursor* cursorHandle);

    imgui_editor::imgui_editor_context* imgui_editor = nullptr;
    imgui_editor::history* history = nullptr;
    imgui_editor::selection_context* selection = nullptr;

    std::string* root = nullptr;

	void (*widget_deserialize)(imgui_editor::widget* target, const char* data);
	bool (*open_project)(imgui_editor::imgui_editor_context* ctx, const char* path);

	std::unordered_map<size_t, imgui_editor::widget*>* widgets;
};

// some global data from our libs we keep in the host so we
// do not need to care about storing/restoring them
// lib의 일부 전역 데이터를 호스트에 보관하므로 저장/복원에 대해 신경 쓸 필요가 없습니다.
static HostData data;
static GLFWwindow* window;

// GLFW callbacks
// You can also handle inputs yourself and use those as a reference.
// 입력을 직접 처리하고 이를 참조로 사용할 수도 있습니다.
void ImGui_ImplGlfwGL3_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void ImGui_ImplGlfwGL3_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void ImGui_ImplGlfwGL3_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void ImGui_ImplGlfwGL3_CharCallback(GLFWwindow* window, unsigned int c);

void ImGui_ImplGlfwGL3_MouseButtonCallback(GLFWwindow*, int button, int action, int /*mods*/)
{
	if (action == GLFW_PRESS && button >= 0 && button < 3)
		data.mousePressed[button] = true;
}

void ImGui_ImplGlfwGL3_ScrollCallback(GLFWwindow*, double /*xoffset*/, double yoffset)
{
	data.mouseWheel += (float)yoffset; // Use fractional mouse wheel, 1.0 unit 5 lines.
}

static const char* ImGui_ImplGlfwGL3_GetClipboardText(void* user_data)
{
	return glfwGetClipboardString((GLFWwindow*)user_data);
}

static void ImGui_ImplGlfwGL3_SetClipboardText(void* user_data, const char* text)
{
	glfwSetClipboardString((GLFWwindow*)user_data, text);
}

void ImGui_ImplGlfwGL3_KeyCallback(GLFWwindow*, int key, int, int action, int mods)
{
	if (action == GLFW_PRESS)
		data.imgui_context->IO.KeysDown[key] = true;
	if (action == GLFW_RELEASE)
		data.imgui_context->IO.KeysDown[key] = false;
}

void ImGui_ImplGlfwGL3_CharCallback(GLFWwindow*, unsigned int c)
{
	if (c > 0 && c < 0x10000)
	{
		int n = 0;
		for (unsigned short* p = data.inputCharacters; *p; p++)
		{
			n++;
		}
		const int len = ((int)(sizeof(data.inputCharacters) / sizeof(*data.inputCharacters)));
		if (n + 1 < len)
		{
			data.inputCharacters[n] = c;
			data.inputCharacters[n + 1] = '\0';
		}
	}
}

imgui_editor::imgui_editor_context editor_context;
imgui_editor::history history;
imgui_editor::selection_context selection;
std::unordered_map<size_t, imgui_editor::widget*> widgets;

void drop_callback(GLFWwindow* window, int count, const char** paths)
{
	for (int i = 0; i < count; i++)
	{
		LOG("Dropped file %s", paths[i]);
	}

	if (1 == count)
	{
		std::ifstream ifs(paths[0]);
		std::string content((std::istreambuf_iterator<char>(ifs)),
		                    (std::istreambuf_iterator<char>()));

		data.open_project(&editor_context, paths[0]);
		// data.widget_deserialize(we.root, content.c_str());
	}
}

int main(int argc, char** argv)
{
	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	CSimpleIniA ini;
	ini.SetUnicode();
	SI_Error rc = ini.LoadFile("imgui_editor.ini");
	if (rc < 0)
	{
		rc = ini.SaveFile("imgui_editor.ini");
		if (rc < 0)
		{
			LOG("failed to save imgui_editor.ini");
		}
	}

	char* stop = nullptr;
	const char* w_string = ini.GetValue("main_window_size", "width");
	const char* h_string = ini.GetValue("main_window_size", "height");

	constexpr int default_width = 1024;
	constexpr int default_height = 768;

	const int width = w_string ? strtod(w_string, &stop) : default_width;
	const int height = h_string ? strtod(h_string, &stop) : default_height;

	window = glfwCreateWindow(width ? width : default_width, height ? height : default_height, "ImGui Editor", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

#ifdef _WIN32
	data.wndh = glfwGetWin32Window(window);
#endif
	data.ImGui_ImplGlfwGL3_SetClipboardText = ImGui_ImplGlfwGL3_SetClipboardText;
	data.ImGui_ImplGlfwGL3_GetClipboardText = ImGui_ImplGlfwGL3_GetClipboardText;
	data.window = window;
	data.imgui_context = ImGui::CreateContext();

	data.imgui_editor = &editor_context;
	data.history = &history;
	data.selection = &selection;

	std::string rootBuffer;
	data.root = &rootBuffer;

	data.widgets = &widgets;

	glfwSetMouseButtonCallback(window, ImGui_ImplGlfwGL3_MouseButtonCallback);
	glfwSetScrollCallback(window, ImGui_ImplGlfwGL3_ScrollCallback);
	glfwSetKeyCallback(window, ImGui_ImplGlfwGL3_KeyCallback);
	glfwSetCharCallback(window, ImGui_ImplGlfwGL3_CharCallback);

	data.glfwSetCursorPosInvoke = glfwSetCursorPos;
	data.glfwGetCursorPosInvoke = glfwGetCursorPos;
	data.glfwGetWindowAttribInvoke = glfwGetWindowAttrib;
	data.glfwGetMouseButtonInvoke = glfwGetMouseButton;
	data.glfwSetInputModeInvoke = glfwSetInputMode;
	data.glfwCreateStandardCursorInvoke = glfwCreateStandardCursor;
	data.glfwGetInputModeInvoke = glfwGetInputMode;
	data.glfwSetInputModeInvoke = glfwSetInputMode;
	data.glfwSetCursorInvoke = glfwSetCursor;

	cr_plugin ctx;
	ctx.userdata = &data;
	cr_plugin_open(ctx, plugin);

	int current_width = width;
	int current_height = height;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glfwGetWindowSize(window, &data.w, &data.h);
		glfwGetFramebufferSize(window, &data.display_w, &data.display_h);
		data.timestep = glfwGetTime();

#ifdef _WIN32
		// if it's a HighDPI monitor, try to scale everything
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		float x_scale, y_scale;
		glfwGetMonitorContentScale(monitor, &x_scale, &y_scale);
		data.high_dpi_factor = x_scale;
		glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
#elif __APPLE__
		// to prevent 1200x800 from becoming 2400x1600
		glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
#endif

		cr_plugin_update(ctx);

		memset(data.inputCharacters, 0, sizeof(data.inputCharacters));

		glfwSwapBuffers(window);

		if (data.imgui_editor->project.ready)
		{
			std::string window_title;
			if (data.imgui_editor->project.dirty) window_title.append("* ");

			std::string project_name = std::filesystem::path(data.imgui_editor->project.absolutePath).stem().string();
			if(project_name.empty())
			{
				project_name = "Untitled";
			}

			window_title.append(string_format("%s - ImGui Editor [%.1f fps]", project_name.c_str(), ImGui::GetIO().Framerate));
			glfwSetWindowTitle(window, window_title.c_str());
		}
		else
		{
			char title[64];
			sprintf(title, "ImGui Editor [%.1f fps]", ImGui::GetIO().Framerate);
			glfwSetWindowTitle(window, title);
		}
		glfwSetDropCallback(window, drop_callback);

		if (data.w != current_width || data.h != current_height)
		{
			current_width = data.w;
			current_height = data.h;
			ini.SetValue("main_window_size", "width", std::to_string(current_width).c_str());
			ini.SetValue("main_window_size", "height", std::to_string(current_height).c_str());
			rc = ini.SaveFile("imgui_editor.ini");

			if (rc < 0)
			{
				LOG("failed to save imgui_editor.ini");
			}
		}

		current_width = data.w;
		current_height = data.h;
	}

	cr_plugin_close(ctx);
	glfwTerminate();

	return 0;
}
