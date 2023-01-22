#ifndef GUI_H
#define GUI_H

//#include <glad/glad.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

//#include "../shader/Shader.h"
#include <iostream>



class Gui {
    bool exit = false;

    GLFWwindow *window;
    const char* glsl_version;
    ImVec4 clear_color;


    int WIDTH;
    int HEIGHT;


public:
    Gui(int width, int height);
    ~Gui();

    void SetupOpenGl();

    void CreateOpenGlWindow(const char* name);
    void DestroyOpenGlWindow() noexcept;

    void CreateImGui();
    static void DestroyImGui() noexcept;

    void BeginRenderer() noexcept;
    void Render() noexcept;
};

#endif //SHADER_EDITOR_GUI_H
