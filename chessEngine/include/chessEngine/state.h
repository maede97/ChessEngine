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
   * @todo Promotion if a pawn reaches the end.
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
   * @todo Not done.
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
   * @brief Get castle information.
   * @param[out] whiteKingSide If the white player can castle king side.
   * @param[out] whiteQueenSide If the white player can castle queen side.
   * @param[out] blackKingSide If the black player can castle king side.
   * @param[out] blackQueenSide If the black player can castle queen side.
   */
  void getCastleInformation(bool &whiteKingSide, bool &whiteQueenSide,
                            bool &blackKingSide, bool &blackQueenSide) const;

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

  /**
   * @brief Get information about the current En-Passant status.
   * @param whiteEnPassant Which column white is En-Passant-ready (-1 if none)
   * @param blackEnPassant Which column black is En-Passant-ready (-1 if none)
   */
  void getEnPassantInformation(int &whiteEnPassant, int &blackEnPassant) const;

  /**
   * @brief Get all captured pieces by color.
   * @param[out] whiteCaptured All pieces that white captured.
   * @param[out] blackCaptured All pieces that black captured.
   */
  void getCapturedPieces(std::vector<Piece> &whiteCaptured,
                         std::vector<Piece> &blackCaptured) const;

  /**
   * @brief Set the promotion type for white.
   *
   * This should be called before performing the pawn-move (reaches end).
   * @param type The type to convert to.
   */
  void setWhitePromotionType(PieceType type);
  /**
   * @brief Set the promotion type for black.
   *
   * This should be called before performing the pawn-move (reaches end).
   * @param type The type to convert to.
   */
  void setBlackPromotionType(PieceType type);

private:
  std::vector<Move> m_moves; ///< All moves previously done in this game.
  Board m_board;             ///< Current Board

  PlayerColor m_nextPlayer =
      PlayerColor::WHITE; ///< The player which comes next. White should start.
  bool m_whiteCastleKingSide =
      true; ///< If the white player can castle king side
  bool m_whiteCastleQueenSide =
      true; ///< If the white player can castle queen side
  bool m_blackCastleKingSide =
      true; ///< If the black player can castle king side
  bool m_blackCastleQueenSide =
      true; ///< If the black player can castle queen side

  unsigned int m_halfMoves = 0; ///< This is the number of halfmoves since the
                                ///< last capture or pawn advance
  unsigned int m_fullMoves = 1; ///< The number of the full move. It starts at
                                ///< 1, and is incremented after Black's move.

  std::vector<Piece>
      m_capturedPiecesWhite; ///< vector to store captured white pieces.
  std::vector<Piece>
      m_capturedPiecesBlack; ///< vector to store captured black pieces

  int m_whiteEnPassant =
      -1; ///< Stores with pawn (column) was just moved (to enable En-Passant)
  int m_blackEnPassant =
      -1; ///< Stores with pawn (column) was just moved (to enable En-Passant)

  PieceType m_whitePromotionType = PieceType::QUEEN;
  PieceType m_blackPromotionType = PieceType::QUEEN;
};

} // namespace chessEngine