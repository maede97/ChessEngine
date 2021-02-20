#include <ChessEngineGui/gui.h>
#include <iostream>
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

  board = new chessEngine::Board(chessEngine::Board::defaultBoard());
}

Application::~Application() {
  glfwDestroyWindow(window);
  glfwTerminate();

  delete board;
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

      // COMBOBOX FOR COLOR

      const char *itemColor[] = {"White", "Black"};
      static const char *current_item_color = "White";
      if (ImGui::BeginCombo("##comboColor", current_item_color)) {
        for (int i = 0; i < IM_ARRAYSIZE(itemColor); i++) {
          bool is_selected = (current_item_color == itemColor[i]);
          if (ImGui::Selectable(itemColor[i], is_selected)) {
            current_item_color = itemColor[i]; // udpate
            currentPlayerColor = chessEngine::PlayerColor(i + 1);

            if (clickedPosition) {
              board->removePiece(*clickedPosition);
              delete clickedPosition;
              clickedPosition = nullptr;
            }
          }
          if (is_selected) {
            ImGui::SetItemDefaultFocus();
          }
        }
        ImGui::EndCombo();
      }

      // COMBOBOX FOR TYPE

      const char *items[] = {"Pawn", "Knight", "Bishop",
                             "Rook", "Queen",  "King"};
      static const char *current_item = "Pawn";

      if (ImGui::BeginCombo("##comboType", current_item)) {
        for (int i = 0; i < IM_ARRAYSIZE(items); i++) {
          bool is_selected = (current_item == items[i]);
          if (ImGui::Selectable(items[i], is_selected)) {
            current_item = items[i]; // udpate
            currentPieceType = chessEngine::PieceType(i + 1);

            if (clickedPosition) {
              board->removePiece(*clickedPosition);
              delete clickedPosition;
              clickedPosition = nullptr;
            }
          }
          if (is_selected) {
            ImGui::SetItemDefaultFocus();
          }
        }
        ImGui::EndCombo();
      }

      // CHECK VALID MOVES

      std::vector<std::vector<bool>> validMoves;

      if (clickedPosition) {
        // check for validity
        validMoves = board->getValidMoves(*clickedPosition);
      }

      // DRAW THE BOARD
      for (int i = 7; i > -1; i--) {
        for (int j = 0; j < 8; j++) {
          ImGui::PushID(i * 8 + j);

          // no spacing between buttons

          ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
          // Push a color based on i and j
          if ((i + j) % 2 != 0) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1, 1, 1, 1));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                                  ImVec4(0.5, 0.5, 0.5, 1));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0, 0, 1));
          } else {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 1));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                                  ImVec4(0.5, 0.5, 0.5, 1));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
          }
          const char *toPrint = " ";
          try {
            // try to get the real value at this position
            chessEngine::Piece pieceAt =
                board->getPiece(chessEngine::Position(i, j));
            toPrint = chessEngine::IO::pieceToCharSimple(pieceAt);
          } catch (std::runtime_error e) {
            // pass
          }
          if (clickedPosition) {
            // if valid move, change the char to print
            if (validMoves.size() > 0 && validMoves[i][j]) {
              chessEngine::Move m = chessEngine::Move(
                  currentPlayerColor, currentPieceType, *clickedPosition,
                  chessEngine::Position(i, j));
              if (board->isAttackMove(m)) {
                toPrint = "X";
              } else {
                toPrint = "O";
              }
            }

            // we have a clicked position, draw this button differently
            if (chessEngine::Position(i, j) == *clickedPosition) {
              if (ImGui::Button(chessEngine::IO::pieceToCharSimple(
                                    currentPlayerColor, currentPieceType),
                                ImVec2(50, 50))) {
                // reset
                board->removePiece(*clickedPosition);
                delete clickedPosition;
                clickedPosition = nullptr;
                validMoves.clear();
              }
            } else {
              if (ImGui::Button(toPrint, ImVec2(50, 50))) {
                // new position
                board->removePiece(*clickedPosition);
                delete clickedPosition;
                clickedPosition = new chessEngine::Position(i, j);
                board->placePiece(
                    *clickedPosition,
                    chessEngine::Piece(currentPieceType, currentPlayerColor));
                // we had a change in the move, recompute the valid moves.
                validMoves = board->getValidMoves(*clickedPosition);
              }
            }
          } else {
            // a button click will set the clickedPosition
            if (ImGui::Button(toPrint, ImVec2(50, 50))) {
              clickedPosition = new chessEngine::Position(i, j);
              board->placePiece(
                  *clickedPosition,
                  chessEngine::Piece(currentPieceType, currentPlayerColor));
              validMoves = board->getValidMoves(*clickedPosition);
            }
          }

          ImGui::SameLine();

          ImGui::PopStyleColor(3);
          ImGui::PopStyleVar();
          ImGui::PopID();
        }
        ImGui::NewLine();
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