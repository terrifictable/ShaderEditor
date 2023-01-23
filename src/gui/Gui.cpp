#include "Gui.h"

#include "themes.h"
#include "../utils.h"


#define DEBUG


Gui::Gui(int width, int height) {
    WIDTH = width;
    HEIGHT = height;
}

Gui::~Gui() {
    Gui::DestroyImGui();
    Gui::DestroyOpenGlWindow();
}




void GlfwErrorCallback(int error, const char* description) {
    std::cerr << "Glfw Error " << error << ": " << description << std::endl;
}

void Gui::SetupOpenGl() {
    glfwSetErrorCallback(GlfwErrorCallback);

    if (!glfwInit())
        throw std::runtime_error("Failed to initialize glfw");
#ifdef DEBUG
    std::cout << "Initialized GLFW" << std::endl;
#endif

    Gui::glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void Gui::CreateOpenGlWindow(const char *name) {
    window = glfwCreateWindow(WIDTH, HEIGHT, name, nullptr, nullptr);
    if (window == nullptr)
        throw std::runtime_error("Failed to create window");
#ifdef DEBUG
    std::cout << "Created GLFW Window" << std::endl;
#endif

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }
#ifdef DEBUG
    std::cout << "Initialized GLAD" << std::endl;
#endif

    glfwSwapInterval(1);
}

void Gui::DestroyOpenGlWindow() noexcept {
    glfwDestroyWindow(window);
    glfwTerminate();
}













void Gui::CreateImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
//     io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//     io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();
//    ImGuiStyle& style = ImGui::GetStyle();
//    style.WindowRounding = 4;
//    style.FrameRounding = 4;
//    style.GrabRounding = 3;
    Theme::PhocosGreen();


    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    io.Fonts->AddFontDefault();
    ImFont* font = io.Fonts->AddFontFromFileTTF("out/roboto.ttf", 15.0f);
    IM_ASSERT(font != nullptr);
    io.FontDefault = font;

#ifdef DEBUG
    std::cout << "Created ImGui window" << std::endl;
#endif
}

void Gui::DestroyImGui() noexcept {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}









void Gui::BeginRenderer() noexcept {
    auto lang = TextEditor::LanguageDefinition::GLSL();
    editor.SetLanguageDefinition(lang);
    editor.SetPalette(TextEditor::GetDarkPalette());

    editor.SetText(readFile("shaders/default.fsh"));

    tr_a =  1.0f; tr_b =  1.0f; tr_c = 0.0f;
    br_a =  1.0f; br_b = -1.0f; br_c = 0.0f;
    bl_a = -1.0f; bl_b = -1.0f; bl_c = 0.0f;
    tl_a = -1.0f; tl_b =  1.0f; tl_c = 0.0f;

    float r_tr[] = { tr_a, tr_b, tr_c };
    float r_br[] = { br_a, br_b, br_c };
    float r_bl[] = { bl_a, bl_b, bl_c };
    float r_tl[] = { tl_a, tl_b, tl_c };
    Rectangle rectangle(r_tl, r_tr, r_bl, r_br);

    shader = {editor.GetText()};
    while (!glfwWindowShouldClose(Gui::window) && !exit) {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        WIDTH = display_w;
        HEIGHT = display_h;

        double mouse_x, mouse_y;
        glfwGetCursorPos(window, &mouse_x, &mouse_y);


        if (Gui::Render() != 0)
            break;

        ImGui::Render();
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.12f, 0.12f, 0.12f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        float _r_tr[] = { tr_a, tr_b, tr_c };
        float _r_br[] = { br_a, br_b, br_c };
        float _r_bl[] = { bl_a, bl_b, bl_c };
        float _r_tl[] = { tl_a, tl_b, tl_c };
        rectangle = {_r_tl, _r_tr, _r_bl, _r_br};

        shader.use();
        glUniform1f(glGetUniformLocation(shader.programID, "time"), glfwGetTime());
        glUniform2f(glGetUniformLocation(shader.programID, "mouse"), mouse_x, mouse_y);
        glUniform2f(glGetUniformLocation(shader.programID, "resolution"), display_w, display_h);
        rectangle.Draw();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    rectangle.Delete();
}




int Gui::Render() noexcept {
//    ImGui::ShowDemoWindow();

    static bool show_editor = true;

    if (show_editor) {
        ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Save", "Ctrl-S")) {
                    auto textToSave = editor.GetText();
                    shader = {textToSave};
                }
                if (ImGui::MenuItem("Quit", "Alt-F4"))
                    return -1;
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, editor.CanUndo()))
                    editor.Undo();
                if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, editor.CanRedo()))
                    editor.Redo();

                ImGui::Separator();

                if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
                    editor.Copy();
                if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, editor.HasSelection()))
                    editor.Cut();
                if (ImGui::MenuItem("Delete", "Del", nullptr, editor.HasSelection()))
                    editor.Delete();
                if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, ImGui::GetClipboardText() != nullptr))
                    editor.Paste();

                ImGui::Separator();

                if (ImGui::MenuItem("Select all", nullptr, nullptr))
                    editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View")) {
                if (ImGui::MenuItem("Dark palette"))
                    editor.SetPalette(TextEditor::GetDarkPalette());
                if (ImGui::MenuItem("Light palette"))
                    editor.SetPalette(TextEditor::GetLightPalette());
                if (ImGui::MenuItem("Retro blue palette"))
                    editor.SetPalette(TextEditor::GetRetroBluePalette());
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        editor.Render("Editor");
        ImGui::End();
    }

    ImGui::Begin("Options");
    if (ImGui::TreeNode("Position")) {
        ImGui::SliderFloat("Top Right X", &tr_a, -1.0f, 1.0f);
        ImGui::SliderFloat("Top Right Y", &tr_b, -1.0f, 1.0f);
        ImGui::Separator();

        ImGui::SliderFloat("Top Left X", &tl_a, -1.0f, 1.0f);
        ImGui::SliderFloat("Top Left Y", &tl_b, -1.0f, 1.0f);
        ImGui::Separator();

        ImGui::SliderFloat("Bottom Right X", &br_a, -1.0f, 1.0f);
        ImGui::SliderFloat("Bottom Right Y", &br_b, -1.0f, 1.0f);
        ImGui::Separator();

        ImGui::SliderFloat("Bottom Left X", &bl_a, -1.0f, 1.0f);
        ImGui::SliderFloat("Bottom Left Y", &bl_b, -1.0f, 1.0f);

        ImGui::TreePop();
    }

    static int style_idx = 0;
    if (ImGui::Combo("Style", &style_idx, "Phocus Green\0Dark\0Light\0Classic\0Maya\0Monochrome\0The_0n3\0ModernDarkTheme\0EmbraceTheDarkness")) {
        switch (style_idx) {
            case 0: Theme::PhocosGreen(); break;
            case 1: ImGui::StyleColorsDark(); break;
            case 2: ImGui::StyleColorsLight(); break;
            case 3: ImGui::StyleColorsClassic(); break;
            case 4: Theme::Maya(); break;
            case 5: Theme::Monochrome(); break;
            case 6: Theme::The_0n3(); break;
            case 7: Theme::ModernDarkTheme(); break;
            case 8: Theme::EmbraceTheDarkness(); break;
        }
    }

    ImGui::Checkbox("Editor", &show_editor);

    ImGui::End();


    return 0;
}

