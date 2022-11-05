#ifndef __CR_WINDOW__
#define __CR_WINDOW__
struct GLFWwindow;
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
    const char* (*get_clipboard_fn)(void* user_data);
    void(*set_clipboard_fn)(void* user_data, const char* text);
    void(*set_cursor_pos_fn)(GLFWwindow* handle, double xpos, double ypos);
    void(*get_cursor_pos_fn)(GLFWwindow* handle, double* xpos, double* ypos);
    int(*get_window_attrib_fn)(GLFWwindow* handle, int attrib);
    int(*get_mouse_button_fn)(GLFWwindow* handle, int button);
    void(*set_input_mode_fn)(GLFWwindow* handle, int mode, int value);
};

/**
 * @author cr545l@gmail.com
*/
class CrWindow
{
public:
    CrWindow(HostData* hostData):_hostData(hostData){}
    
    void OnGUI();
    
private:
    HostData* _hostData;
};

#endif
