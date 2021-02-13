#pragma once
#include "definitions.h"

/** 
 * A chess Piece
 */
class Piece
{
public:
    Piece() = delete;
    Piece(PieceType type, PlayerColor color);

    // getters
    PieceType type() const;
    PlayerColor color() const;

    // setters by reference
    PieceType& type();
    PlayerColor& color();

private:
    PieceType m_type;
    PlayerColor m_color;
};