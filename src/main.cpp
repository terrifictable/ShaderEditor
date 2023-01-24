
#include "gui/Gui.h"

int main() {
    Gui gui{1920, 1080};

    gui.SetupOpenGl();

    gui.CreateOpenGlWindow("Shader TextEditor");
    gui.CreateImGui();

    gui.BeginRenderer();

    return 0;
}
