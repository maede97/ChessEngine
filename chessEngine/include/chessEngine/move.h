#pragma once

#include <chessEngine/definitions.h>
#include <chessEngine/position.h>
#include <iostream>

namespace chessEngine {

/**
 * @brief This class contains information about a single move on the game
 */
class Move {
public:
  /**
   * @brief The default constructor is not allowed.
   */
  Move() = delete;

  /**
   * @brief Create a player move with a piece with start and end positions.
   * @param player The player which took this move.
   * @param piece The type of piece which makes this move.
   * @param from The starting position of this move.
   * @param to The end position of this move.
   */
  Move(PlayerColor player, PieceType piece, Position from, Position to);

  /**
   * @brief Getter for the player.
   */
  PlayerColor player() const;

  /**
   * @brief Getter for the piece.
   */
  PieceType piece() const;

  /**
   * @brief Getter for the start position.
   */
  Position from() const;

  /**
   * @brief Getter for the end position.
   */
  Position to() const;

  /**
   * @brief Setter for the player.
   */
  PlayerColor &player();

  /**
   * @brief Setter for the piece.
   */
  PieceType &piece();

  /**
   * @brief Setter for start position.
   */
  Position &from();

  /**
   * @brief Setter for end position.
   */
  Position &to();

  /**
   * @brief Checks if this move is valid based on the current piece.
   * @param attack Whether this piece attacks with this move (required for
   * proper Pawn movement check).
   * @attention This does not check for pieces inbetween! En-Passant is
   * implemented with attack=true. Castling is also implemented.
   */
  bool isValid(bool attack = false) const;

private:
  PlayerColor m_player; ///< Internal player storage.
  PieceType m_piece;    ///< Internal piece storage.
  Position m_from;      ///< Internal start position storage.
  Position m_to;        ///< Internal end position storage.
};

} // namespace chessEngine

/**
 * @brief Write move information to the output stream.
 * @param os The stream to write to.
 * @param move The move to write out.
 */
std::ostream &operator<<(std::ostream &os, const chessEngine::Move &move);