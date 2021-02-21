#include <ChessEngineGui/gui.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <ChessEngineGui/logger.h>

#include <chessEngine/io.h>

CHESS_NAMESPACE_BEGIN

Application::Application(int width, int height, const char *title)
    : width(width), height(height) {
  if (!glfwInit()) {
    MAKE_ERROR("Could not init.");
  }

  // set callback
  glfwSetErrorCallback(Application::error_callback);

  // create window with OpenGL3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (!window) {
    MAKE_ERROR("Could not create Window.");
  }

  // make context to use OpenGL functions on this window
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
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
  // ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 130");
}

Application::~Application() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void Application::run() {
  const size_t blockSizeBytes = 3 * width * height * sizeof(unsigned char);

  unsigned char *device_pixels = nullptr;
  size_t buffer_size;

  while (!glfwWindowShouldClose(window)) {
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

      ImGui::Begin("Board");

      // show next player
      if (game.getNextPlayer() == chessEngine::PlayerColor::WHITE) {
        ImGui::Text("Next Player: White");
      } else {
        ImGui::Text("Next Player: Black");
      }

      bool isValid = false;
      bool isCheck = false;
      bool isAttack = false;
      bool isCurrent = false;

      // DRAW THE BOARD
      for (int i = 7; i > -1; i--) {
        for (int j = 0; j < 8; j++) {
          isValid = false;
          isCheck = false;
          isAttack = false;
          isCurrent = false;

          ImGui::PushID(i * 8 + j);

          // no spacing between buttons

          ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
          // Push a color based on i and j
          if ((i + j) % 2 != 0) {
            // white
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1, 1, 1));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                                  ImVec4(0.5, 0.5, 0.5, 1));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1));
          } else {
            // black
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 1));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                                  ImVec4(0.5, 0.5, 0.5, 1));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
          }

          const char *toPrint = " ";
          try {
            // try to get the real value at this position
            chessEngine::Piece pieceAt =
                game.getBoard().getPiece(chessEngine::Position(i, j));
            toPrint = chessEngine::IO::pieceToCharSimple(pieceAt);
          } catch (std::runtime_error e) {
          }

          // show different colors based on the currently selected piece.
          if (clickedPosition) {
            chessEngine::Piece piece =
                game.getBoard().getPiece(*clickedPosition);
            chessEngine::Move m =
                chessEngine::Move(piece.color(), piece.type(), *clickedPosition,
                                  chessEngine::Position(i, j));

            // set booleans based on the property.
            if (game.isValid(m)) {
              isValid = true;
              if (game.getBoard().isAttackMove(m)) {
                isAttack = true;
              }
              if (game.getBoard().isCheckMove(m)) {
                isCheck = true;
              }
            }

            if (*clickedPosition == chessEngine::Position(i, j)) {
              isCurrent = true;
            }

            // now push style colors based on the properties of the current
            // field.
            if (isValid) {
              // light blue
              ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6, 0.84, 0.9, 1));
            }

            if (isAttack) {
              // light red
              ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7, 0, 0, 1));
            }

            if (isCheck) {
              // dark red, force white color
              ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2, 0, 0, 1));
              ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
            }

            if (isCurrent) {
              // make a green square and force dark font
              ImGui::PushStyleColor(ImGuiCol_Button,
                                    ImVec4(0.56, 0.93, 0.59, 1));
              ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1));
            }
          }

          bool performMove = false;
          if (ImGui::Button(toPrint, ImVec2(50, 50))) {
            // a button was clicked, perform action based on state.

            if (clickedPosition) {
              // second click, perform move if valid.
              chessEngine::Piece piece =
                  game.getBoard().getPiece(*clickedPosition);

              if (game.getBoard().hasPiece(chessEngine::Position(i, j))) {
                // check if there is a piece with our color
                chessEngine::Piece newPiece =
                    game.getBoard().getPiece(chessEngine::Position(i, j));
                if (newPiece.color() == game.getNextPlayer()) {
                  // reset the clicked position to this
                  delete clickedPosition;
                  clickedPosition = new chessEngine::Position(i, j);
                } else {
                  performMove = true;
                }
              } else {
                performMove = true;
              }
              if (performMove) {
                chessEngine::Move move = chessEngine::Move(
                    piece.color(), piece.type(), *clickedPosition,
                    chessEngine::Position(i, j));
                try {
                  std::cout << move << std::endl;
                  game.applyMove(move);

                  std::stringstream ss;
                  ss << "Moved from " << *clickedPosition << " to "
                     << chessEngine::Position(i, j) << ".";
                  Logger::logInfo(ss.str());

                  delete clickedPosition;
                  clickedPosition = nullptr;
                } catch (const std::runtime_error e) {
                  Logger::logWarning("This move is not valid.");
                }
              }
            } else {
              // first button, check if this piece is actually valid to play.
              try {
                if (game.getBoard()
                        .getPiece(chessEngine::Position(i, j))
                        .color() == game.getNextPlayer()) {
                  // valid.
                  clickedPosition = new chessEngine::Position(i, j);
                } else {
                  Logger::logWarning("This piece is not valid.");
                }
              } catch (std::runtime_error e) {
                Logger::logWarning("No piece there.");
              }
            }
          }

          if (isCurrent) {
            ImGui::PopStyleColor(2);
          }
          if (isValid) {
            ImGui::PopStyleColor();
          }
          if (isCheck) {
            // remove dark font as well
            ImGui::PopStyleColor(2);
          }
          if (isAttack) {
            ImGui::PopStyleColor();
          }

          ImGui::SameLine();

          ImGui::PopStyleColor(3);
          ImGui::PopStyleVar();
          ImGui::PopID();
        }
        ImGui::NewLine();
      }

      // print check info
      bool wC, bC;
      game.getBoard().getCheckInfo(wC, bC);
      if (wC) {
        ImGui::Text("White in check!");
      }
      if (bC) {
        ImGui::Text("Black in check!");
      }

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

void Application::button_callback(GLFWwindow *window, int button, int action,
                                  int mods) {
  Application *app =
      static_cast<Application *>(glfwGetWindowUserPointer(window));
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    double mX, mY;
    glfwGetCursorPos(window, &mX, &mY);
  }
}

void Application::error_callback(int error, const char *description) {
  MAKE_ERROR(description);
}

void Application::key_callback(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
  Application *app =
      static_cast<Application *>(glfwGetWindowUserPointer(window));
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

void Application::updateSize(int width, int height) {
  this->width = width;
  this->height = height;
}

void Application::resize_callback(GLFWwindow *window, int width, int height) {
  Application *app =
      static_cast<Application *>(glfwGetWindowUserPointer(window));
  glViewport(0, 0, width, height);
  app->updateSize(width, height);
}

CHESS_NAMESPACE_END