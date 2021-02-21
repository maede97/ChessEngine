#pragma once

#include <ChessEngineGui/timer.h>
#include <ChessEngineGui/utils.h>

#include <chessEngine/state.h>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <imgui.h>

CHESS_NAMESPACE_BEGIN

class Application {
public:
  Application(int width = 1200, int height = 800,
              const char *title = "ChessEngineGui");

  ~Application();

  /**
   * Run this app
   */
  void run();

  void updateSize(int width, int height);

private:
  static void error_callback(int error, const char *description);
  static void key_callback(GLFWwindow *window, int key, int scancode,
                           int action, int mods);
  static void resize_callback(GLFWwindow *window, int width, int height);
  static void button_callback(GLFWwindow *window, int button, int action,
                              int mods);

  // GLFW stuff
  GLFWwindow *window;
  int width, height;

  Timer fpsTimer;

  chessEngine::GameState game;
  chessEngine::Position *clickedPosition = nullptr;
};

CHESS_NAMESPACE_END