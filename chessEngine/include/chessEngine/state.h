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
   * @brief Checks if a move is valid.
   *
   * This takes into account the move validity but also the current game state
   * (en-passant, castling, check, etc).
   * @param move The move to check.
   * @todo This is still incomplete.
   */
  bool isValid(const Move &move) const;

  /**
   * @brief Get all valid moves for the current piece at the position given.
   *
   * Internally relies on applyMove, therefore still incomplete.
   * @todo Still not done.
   * @param position The position to get all valid moves for.
   */
  std::vector<std::vector<bool>> getValidMoves(const Position &position) const;

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

  PlayerColor m_nextPlayer =
      PlayerColor::WHITE; ///< The player which comes next. White should start.
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

  std::vector<Piece>
      m_capturedPiecesWhite; ///< vector to store captured white pieces.
  std::vector<Piece>
      m_capturedPiecesBlack; ///< vector to store captured black pieces

  // TODO: store enpassant information
  // TODO: store castle information
};

} // namespace chessEngine