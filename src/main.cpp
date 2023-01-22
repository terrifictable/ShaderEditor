#include <imgui/imgui.h>
#include <iostream>


#include "gui/Gui.h"

int main() {
    Gui gui{1920, 1080};

    gui.SetupOpenGl();
    gui.CreateOpenGlWindow("Hello World!");

    gui.CreateImGui();
    gui.BeginRenderer();

    // Automatically destroy imgui and opengl window using class destructor

    return 0;
}
