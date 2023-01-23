#ifndef GUI_H
#define GUI_H

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../OpenGL/Shader/Shader.h"
#include "../imgui/TextEditor.h"
#include "../OpenGL/Shape/Shapes/Rectangle.h"

#include <iostream>


class Gui {
    bool exit = false;

    GLFWwindow *window;
    const char* glsl_version;
    ImVec4 clear_color;


    float tr_a, tr_b, tr_c;
    float br_a, br_b, br_c;
    float bl_a, bl_b, bl_c;
    float tl_a, tl_b, tl_c;

    TextEditor editor;
    Shader shader{};

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
    int Render() noexcept;
};

#endif //SHADER_EDITOR_GUI_H
