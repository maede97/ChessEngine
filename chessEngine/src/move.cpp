#include <chessEngine/move.h>

Move::Move(PlayerColor player, PieceType piece, Position from, Position to) : m_player(player), m_piece(piece), m_from(from), m_to(to) {}

PlayerColor Move::player() const { return m_player; }
PieceType Move::piece() const { return m_piece; }
Position Move::from() const { return m_from; }
Position Move::to() const { return m_to; }

PlayerColor &Move::player() { return m_player; }
PieceType &Move::piece() { return m_piece; }
Position &Move::from() { return m_from; }
Position &Move::to() { return m_to; }