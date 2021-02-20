#pragma once
#include <chessEngine/board.h>
#include <chessEngine/definitions.h>
#include <chessEngine/move.h>

#include <vector>
namespace chessEngine {
/**
 * @brief Class to hold the current state of the game
 * @todo This class is still incomplete. In addition, all unittests are still
 * needed.
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

  /**
   * @brief Applies a full chess move.
   * @param move The move to apply.
   * @throws std::runtime_error If the move is from the wrong player or if the
   * move is invalid.
   */
  void applyMove(const Move &move);

  /**
   * @brief Set the next player to play.
   * @param next The player which can play next.
   */
  void setNextPlayer(PlayerColor next);

  /**
   * @brief Returns the next player to play.
   */
  PlayerColor getNextPlayer() const;

  /**
   * @brief Set castle information.
   * @param whiteKingSide If the white player can castle king side.
   * @param whiteQueenSide If the white player can castle queen side.
   * @param blackKingSide If the black player can castle king side.
   * @param blackQueenSide If the black player can castle queen side.
   */
  void setCastleInformation(bool whiteKingSide, bool whiteQueenSide,
                            bool blackKingSide, bool blackQueenSide);

  /**
   * @brief Sets the half moves. That is the number of halfmoves since the last
   * capture or pawn advance.
   * @param halfMoves The number to set.
   */
  void setHalfMoves(unsigned int halfMoves);

  /**
   * @brief Sets the full moves. Starts at 1 and gets increased after blacks
   * move.
   * @param fullMoves The number to set.
   */
  void setFullMoves(unsigned int fullMoves);

private:
  std::vector<Move> m_moves; ///< All moves previously done in this game.
  Board m_board;             ///< Current Board

  PlayerColor m_nextPlayer; ///< The player which comes next.
  bool m_whiteCastleKingSide =
      false; ///< If the white player can castle king side
  bool m_whiteCastleQueenSide =
      false; ///< If the white player can castle queen side
  bool m_blackCastleKingSide =
      false; ///< If the black player can castle king side
  bool m_blackCastleQueenSide =
      false; ///< If the black player can castle queen side

  unsigned int m_halfMoves = 0; ///< This is the number of halfmoves since the
                                ///< last capture or pawn advance
  unsigned int m_fullMoves = 1; ///< The number of the full move. It starts at
                                ///< 1, and is incremented after Black's move.

  // TODO: store enpassant information
};

} // namespace chessEngine