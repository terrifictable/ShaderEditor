#include "Gui.h"
#include "../VAO/VAO.h"
#include "../EBO/EBO.h"
#include "../Shape/Shapes/Rectangle.h"

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
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 4;
    style.FrameRounding = 4;
    style.GrabRounding = 3;


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
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    Shader shader{"shaders/default.vsh", "shaders/default.fsh"};

    float r_tr[] = {  0.5f,  0.5f, 0.0f };
    float r_br[] = {  0.5f, -0.5f, 0.0f };
    float r_bl[] = { -0.5f, -0.5f, 0.0f };
    float r_tl[] = { -0.5f,  0.5f, 0.0f };
    Rectangle rectangle(r_tl, r_tr, r_bl, r_br);


    while (!glfwWindowShouldClose(Gui::window) && !exit) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
//        ImGui::SetNextWindowSize(ImVec2(display_w, display_h));
//        ImGui::SetNextWindowPos(ImVec2(0, 0));


        Gui::Render();


        ImGui::Render();
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.12f, 0.12f, 0.12f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        rectangle.Draw(shader);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    rectangle.Delete();
}




void Gui::Render() noexcept {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!", nullptr, /* ImGuiWindowFlags_NoResize */ 0);
    ImGui::Text("This is some useful text.");

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::ColorEdit3("clear color", (float*)&clear_color);

    if (ImGui::Button("Button"))
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}
