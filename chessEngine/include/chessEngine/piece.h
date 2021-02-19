#pragma once
#include "definitions.h"
#include <iostream>

namespace chessEngine {
/**
 * @brief Representation of a chess piece.
 */
class Piece {
public:
  /**
   * @brief We do not allow the default constructor.
   */
  Piece() = delete;
  /**
   * @brief Construct a piece from a type and a color.
   * @param type The PieceType to be used.
   * @param color The PlayerColor to be used.
   */
  Piece(PieceType type, PlayerColor color);

  /**
   * @brief Getter for the type.
   */
  PieceType type() const;
  /**
   * @brief Getter for the color.
   */
  PlayerColor color() const;

  /**
   * @brief Setter for the type.
   */
  PieceType &type();
  /**
   * @brief Setter for the color.
   */
  PlayerColor &color();

  /**
   * @brief Helper to check for equality of two pieces.
   * @param rhs The other piece to check against.
   * @return Whether the two pieces are equal (in color and type).
   */
  bool operator==(const Piece &rhs) const;

  /**
   * @brief Helper to check for inequality of two pieces.
   * @param rhs The other piece to check against.
   * @return Whether the two pieces are not equal (in color or type).
   */
  bool operator!=(const Piece &rhs) const;

private:
  PieceType m_type;    ///< Internal type
  PlayerColor m_color; ///< Internal color
};

} // namespace chessEngine

/**
 * @brief Print a piece to a stream.
 * @param os The stream to write to.
 * @param piece The piece to print.
 */
std::ostream &operator<<(std::ostream &os, const chessEngine::Piece &piece);