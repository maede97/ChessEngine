#include <chessEngine/piece.h>

Piece::Piece(PieceType type, PlayerColor color) : m_type(type), m_color(color)
{
}

PieceType Piece::type() const { return m_type; }
PlayerColor Piece::color() const { return m_color; }

PieceType& Piece::type() { return m_type; }
PlayerColor& Piece::color() { return m_color; }