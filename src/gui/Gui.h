#ifndef GUI_H
#define GUI_H


#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../OpenGL/Shader/Shader.h"
#include "../imgui/TextEditor/TextEditor.h"
#include "../OpenGL/Shape/Shapes/Rectangle.h"

//#define ZEP_SINGLE_HEADER_BUILD
//#include <zep.h>

#include <iostream>


class Gui {
    bool exit = false;

    GLFWwindow *window;
    const char* glsl_version;
    bool show_shader_window;

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
