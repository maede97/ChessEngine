#include <chessEngine/board.h>
#include <chessEngine/io.h>
#include <iostream>
#include <stdexcept>

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

void Board::placePiece(const Position &position, const Piece &piece) {
  // check if we already have a piece in this position.
  if (m_board.find(position) != m_board.cend()) {
    throw std::runtime_error("There is already a piece in this position.");
  }

  m_board.emplace(position, piece);
}

void Board::removePiece(const Position &position) {
  if (m_board.find(position) == m_board.cend()) {
    throw std::runtime_error("There is no piece in this position.");
  }
  int erased = m_board.erase(position);
  if (erased == 0) {
    throw std::runtime_error("Could not erase this position.");
  } else {
  }
}

Piece Board::getPiece(const Position &position) const {
  map_t::const_iterator it = m_board.find(position);
  if (it == m_board.cend()) {
    throw std::runtime_error("There is no piece in this position.");
  }
  return it->second;
}

bool Board::operator==(const Board &other) const {
  // there are three cases:
  // 1. the two boards do not have the same number of pieces --> not equal
  // 2. the two boards have the same number of pieces AND some are not in the
  // same position --> not equal
  // 3. the two boards have the same number of pieces AND ALL are in the same
  // position --> equal
  if (numPieces() != other.numPieces()) {
    // case 1
    return false;
  }
  for (auto piece : m_board) {
    try {
      Piece other_p = other.getPiece(piece.first);

      if (other_p != piece.second) {
        // case 2: we have a different piece in this position
        return false;
      }
    } catch (std::runtime_error e) {
      // case 2: there is an empty position on the second board
      return false;
    }
  }
  // case 3
  return true;
}

bool Board::operator!=(const Board &other) const { return !operator==(other); }

void Board::applyMove(const Move &move) {
  auto found = m_board.find(move.from());
  if (found == m_board.cend()) {
    throw std::runtime_error(
        "This move is not valid because the from position is actually empty.");
  }
  if (found->second.type() != move.piece() ||
      found->second.color() != move.player()) {
    throw std::runtime_error(
        "This move is invalid because the piece does not match.");
  }
  Piece currentPiece = found->second;

  auto to = m_board.find(move.to());
  if (to != m_board.cend()) {
    // the to location is not empty
    // we throw an error here, because this field should be empty
    throw std::runtime_error("Move to location is not empty. Move invalid.");
  }

  // now move the piece
  // --> remove it in the old place and add in the new
  removePiece(move.from());
  placePiece(move.to(), currentPiece);
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
  os << IO::writeBoardToString(board);
  return os;
}