#pragma once
#include <chessEngine/board.h>
#include <chessEngine/definitions.h>
#include <chessEngine/move.h>

#include <vector>
namespace chessEngine {
/**
 * @brief Class to hold the current state of the game
 * @todo This class is still incomplete.
 */
class GameState {
public:
  /**
   * Create a new state
   */
  GameState();

  /**
   * @brief Sets the board of this GameState.
   * @param board The board to set.
   */
  void setBoard(const Board &board);

  /**
   * @brief Returns the current board.
   */
  Board getBoard() const;

private:
  std::vector<Move> m_moves; ///< All moves previously done in this game.
  Board m_board;             ///< Current Board
};

} // namespace chessEngine