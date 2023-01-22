#ifndef GUI_H
#define GUI_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "../shader/Shader.h"



class Gui {
    bool exit = false;

    GLFWwindow *window;
    const char* glsl_version;
    ImVec4 clear_color;


    int WIDTH;
    int HEIGHT;

    static void FramebufferSizeCallback(GLFWwindow *window, int width, int height);

public:
    Gui(int width, int height);
    ~Gui();

//    void GlfwErrorCallback(int error, const char* description);
    void SetupOpenGl();

    void CreateOpenGlWindow(const char* name);
    void DestroyOpenGlWindow() noexcept;

    void CreateImGui();
    static void DestroyImGui() noexcept;

    void BeginRenderer() noexcept;
    void Render() noexcept;
};

#endif //SHADER_EDITOR_GUI_H
