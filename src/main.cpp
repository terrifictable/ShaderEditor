
#include "gui/Gui.h"

int main() {
    Gui gui{1920, 1080};

    gui.SetupOpenGl();

    gui.CreateOpenGlWindow("Shader Editor!");
    gui.CreateImGui();

    gui.BeginRenderer();

    return 0;
}
