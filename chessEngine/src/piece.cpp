#include <chessEngine/io.h>
#include <chessEngine/piece.h>

using namespace chessEngine;

Piece::Piece(PieceType type, PlayerColor color)
    : m_type(type), m_color(color) {}

Piece::Piece(PlayerColor color, PieceType type) : Piece(type, color) {}

PieceType Piece::type() const { return m_type; }
PlayerColor Piece::color() const { return m_color; }

PieceType &Piece::type() { return m_type; }
PlayerColor &Piece::color() { return m_color; }

bool Piece::operator==(const Piece &rhs) const {
  return this->m_color == rhs.m_color && this->m_type == rhs.m_type;
}

bool Piece::operator!=(const Piece &rhs) const { return !operator==(rhs); }

std::ostream &operator<<(std::ostream &out, const Piece &piece) {
  out << IO::pieceToCharSimple(piece);
  return out;
}