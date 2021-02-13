#include <ChessEngine/gui.h>
#include <stdexcept>
#include <iostream>
#include <vector>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <ChessEngine/logger.h>

CHESS_NAMESPACE_BEGIN

Application::Application(int width, int height, const char *title) : width(width), height(height)
{
    if (!glfwInit())
    {
        MAKE_ERROR("Could not init.");
    }

    // set callback
    glfwSetErrorCallback(Application::error_callback);

    // create window with OpenGL3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        MAKE_ERROR("Could not create Window.");
    }

    // make context to use OpenGL functions on this window
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        MAKE_ERROR("GLAD could not load OpenGL");
    }

    glfwSetKeyCallback(window, Application::key_callback);
    glfwSetFramebufferSizeCallback(window, Application::resize_callback);
    glfwSetMouseButtonCallback(window, Application::button_callback);

    glfwSwapInterval(1);

    glfwSetWindowUserPointer(window, this);

    glViewport(0, 0, width, height);

    // Setup ImGui
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().ConfigDockingWithShift = false;
    //ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

Application::~Application()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::run()
{
    const size_t blockSizeBytes = 3 * width * height * sizeof(unsigned char);

    unsigned char *device_pixels = nullptr;
    size_t buffer_size;

    while (!glfwWindowShouldClose(window))
    {
        fpsTimer.start();

        // ImGui

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            // Draw all imgui stuff here
            ImGui::Begin("Log");
            Logger::displayConsole(10);
            ImGui::End();
        }

        ImGui::Render();

        ImGui::UpdatePlatformWindows();
        glViewport(0, 0, width, height);
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}

void Application::button_callback(GLFWwindow *window, int button, int action, int mods)
{
    Application *app = static_cast<Application *>(glfwGetWindowUserPointer(window));
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double mX, mY;
        glfwGetCursorPos(window, &mX, &mY);
    }
}

void Application::error_callback(int error, const char *description)
{
    MAKE_ERROR(description);
}

void Application::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Application *app = static_cast<Application *>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void Application::updateSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

void Application::resize_callback(GLFWwindow *window, int width, int height)
{
    Application *app = static_cast<Application *>(glfwGetWindowUserPointer(window));
    glViewport(0, 0, width, height);
    app->updateSize(width, height);
}

CHESS_NAMESPACE_END