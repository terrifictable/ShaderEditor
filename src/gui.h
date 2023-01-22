#ifndef GUI_H
#define GUI_H

#include <GLFW/glfw3.h>
#include "imgui/imgui.h"


namespace gui {
    // CONSTANT WINDOW SIZE
    constexpr int WIDTH  = 1920;
    constexpr int HEIGHT = 1080;

    inline bool exit = false;

    inline GLFWwindow* window;
    inline char *glsl_version;
    inline ImVec4 clear_color;


    void GlfwErrorCallback(int error, const char* description);
    void SetupOpenGl();

    void CreateOpenGlWindow(const char* name);
    void DestroyOpenGlWindow() noexcept;

    void CreateImGui();
    void DestroyImGui() noexcept;

    void BeginRenderer() noexcept;
    void Render() noexcept;
}

#endif //SHADER_EDITOR_GUI_H
