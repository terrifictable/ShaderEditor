#include <imgui/imgui.h>
#include <iostream>

#include "gui.h"

int main() {
    std::cout << "Hello World!" << std::endl;

    gui::SetupOpenGl();
    gui::CreateOpenGlWindow("Hello World!");

    gui::CreateImGui();
    gui::BeginRenderer();

    gui::DestroyImGui();
    gui::DestroyOpenGlWindow();

    return 0;
}
