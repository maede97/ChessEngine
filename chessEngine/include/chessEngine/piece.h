#pragma once
#include "definitions.h"

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

private:
  PieceType m_type;    ///< Internal type
  PlayerColor m_color; ///< Internal color
};

} // namespace chessEngine