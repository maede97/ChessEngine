#include <ChessEngine/utils.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ChessEngine/timer.h>

#include <imgui.h>

CHESS_NAMESPACE_BEGIN

class Application
{
public:
    Application(int width = 1200, int height = 800, const char *title = "ChessEngine");

    ~Application();

    /**
     * Run this app
     */
    void run();

    void updateSize(int width, int height);

private:
    static void error_callback(int error, const char *description);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void resize_callback(GLFWwindow *window, int width, int height);
    static void button_callback(GLFWwindow *window, int button, int action, int mods);

    // GLFW stuff
    GLFWwindow *window;
    int width, height;

    Timer fpsTimer;
};

CHESS_NAMESPACE_END