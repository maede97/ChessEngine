#include <chessEngine/board.h>

using namespace chessEngine;

Board Board::defaultBoard() {
  Board::map_t map;

  map.reserve(64);

  // place white pieces
  map.emplace(Position(0, 0), Piece(PieceType::ROOK, PlayerColor::WHITE));
  map.emplace(Position(0, 1), Piece(PieceType::KNIGHT, PlayerColor::WHITE));
  map.emplace(Position(0, 2), Piece(PieceType::BISHOP, PlayerColor::WHITE));
  map.emplace(Position(0, 3), Piece(PieceType::QUEEN, PlayerColor::WHITE));
  map.emplace(Position(0, 4), Piece(PieceType::KING, PlayerColor::WHITE));
  map.emplace(Position(0, 5), Piece(PieceType::BISHOP, PlayerColor::WHITE));
  map.emplace(Position(0, 6), Piece(PieceType::KNIGHT, PlayerColor::WHITE));
  map.emplace(Position(0, 7), Piece(PieceType::ROOK, PlayerColor::WHITE));
  for (int i = 0; i < 8; i++)
    map.emplace(Position(1, i), Piece(PieceType::PAWN, PlayerColor::WHITE));

  // place black pieces
  map.emplace(Position(7, 0), Piece(PieceType::ROOK, PlayerColor::BLACK));
  map.emplace(Position(7, 1), Piece(PieceType::KNIGHT, PlayerColor::BLACK));
  map.emplace(Position(7, 2), Piece(PieceType::BISHOP, PlayerColor::BLACK));
  map.emplace(Position(7, 3), Piece(PieceType::QUEEN, PlayerColor::BLACK));
  map.emplace(Position(7, 4), Piece(PieceType::KING, PlayerColor::BLACK));
  map.emplace(Position(7, 5), Piece(PieceType::BISHOP, PlayerColor::BLACK));
  map.emplace(Position(7, 6), Piece(PieceType::KNIGHT, PlayerColor::BLACK));
  map.emplace(Position(7, 7), Piece(PieceType::ROOK, PlayerColor::BLACK));
  for (int i = 0; i < 8; i++)
    map.emplace(Position(6, i), Piece(PieceType::PAWN, PlayerColor::BLACK));

  return Board(map);
}
Board Board::emptyBoard() {
  Board::map_t map;
  return Board(map);
}

Board::Board(Board::map_t positions) : m_board(positions) {}

size_t Board::numPieces() const { return m_board.size(); }