#pragma once
#include <chessEngine/state.h>
namespace chessEngine {
/**
 * @brief This class tries to implement a ChessAI.
 */
class AI {
public:
  /**
   * @brief This is not allowed.
   */
  AI() = delete;
  /**
   * @brief Create the AI.
   * @param game The current gamestate.
   */
  AI(const GameState *game);
  /**
   * @brief Deconstruct the AI.
   */
  ~AI();
  /**
   * @brief Get the next best move for the current player.
   */
  Move getBestNextMove();

  /**
   * @brief Enumerates all possible moves.
   * @param depth The depth of the search (half-moves).
   *
   * These numbers should be:
   * depth 1: 20
   * depth 2: 400
   * depth 3: 8902
   * depth 4: 197281
   * depth 5: 4865609
   * @todo The numbers don't add up for depth 4 and 5. Needs further
   * investigation.
   */
  int enumerateAllMoves(int depth);

private:
  /**
   * @brief Helper for the recursive enumeration
   * @param depth The depth of the search.
   * @param state The gamestate to use.
   */
  int countRecursive(int depth, GameState state);
  GameState *m_game = nullptr; ///< keep the original gamestate.
};

} // namespace chessEngine