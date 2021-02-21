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

  if (!isValid(move)) {
    throw std::runtime_error("This move is not valid.");
  }

  auto it = m_board.find(move.to());
  if (it != m_board.cend()) {
    // there is a piece, check for opposite color
    // could also use isAttackMove(), but this would require more runtime due to
    // the second check to move validity.
    if (it->second.color() != move.player()) {
      // remove this piece
      removePiece(move.to());
    }
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

std::vector<std::vector<bool>>
Board::getValidMoves(const Position &position) const {
  std::vector<std::vector<bool>> ret;
  std::vector<bool> empty;
  empty.resize(8, false);
  ret.resize(8, empty);

  auto it = m_board.find(position);
  if (it == m_board.cend()) {
    throw std::runtime_error("There is no piece in this position.");
  }

  for (int i = 7; i > -1; i--) {
    for (int j = 0; j < 8; j++) {
      ret[i][j] = isValid(Move(it->second.color(), it->second.type(), it->first,
                               Position(i, j)));
    }
  }

  return ret;
}

bool Board::isValid(const Move &move) const {
  // if the move is not possible with this piece, return not valid.
  // this takes into account both attack moves (pawns) and normal moves
  if (!move.isValid() && !move.isValid(true)) {
    return false;
  }

  switch (move.piece()) {
  case PieceType::PAWN: {
    // check if a piece is in front, front left or front right
    bool canAttack = false;
    // check if valid with attack
    if (move.isValid(true)) {
      // sideways, check to field
      auto it = m_board.find(move.to());
      if (it == m_board.cend()) {
        // check if a pawn is one further (en-passant)
        if (move.player() == PlayerColor::WHITE) {
          auto it2 =
              m_board.find(Position(move.to().row() - 1, move.to().col()));
          if (it2 != m_board.cend()) {
            return it2->second.type() == PieceType::PAWN &&
                   it2->second.color() == PlayerColor::BLACK;
          } else {
            return false;
          }
        } else {
          auto it2 =
              m_board.find(Position(move.to().row() + 1, move.to().col()));
          if (it2 != m_board.cend()) {
            return it2->second.type() == PieceType::PAWN &&
                   it2->second.color() == PlayerColor::WHITE;
          } else {
            return false;
          }
        }

        // no piece is there
        return false;
      }
      if (it->second.color() != move.player()) {
        return true;
      } else {
        return false;
      }
    }

    if (move.isValid()) {
      // valid without attack --> straight, check for distance
      if (std::abs(move.from().row() - move.to().row()) == 1) {
        // check if piece there
        auto it = m_board.find(move.to());
        if (it == m_board.cend()) {
          return true;
        }
        return false;
      } else {
        // check both places (1 and 2)
        int midRow =
            move.from().row() + (move.to().row() - move.from().row()) / 2;
        auto it = m_board.find(Position(midRow, move.from().col()));
        if (it == m_board.cend()) {
          return true;
        }
        return false;
      }
    }

    break;
  }
  case PieceType::BISHOP: {
    // start from center and go outwards
    int i = move.from().row();
    int j = move.from().col();

    int next_i = (move.to().row() - move.from().row()) /
                 std::abs(move.to().row() - move.from().row());
    int next_j = (move.to().col() - move.from().col()) /
                 std::abs(move.to().col() - move.from().col());

    while (Position(i, j) != move.to()) {
      i += next_i;
      j += next_j;
      auto it = m_board.find(Position(i, j));
      if (it != m_board.cend()) {
        // if we are at the desired location, and the piece is of opponent
        // color, the move is valid
        if (Position(i, j) == move.to() &&
            it->second.color() != move.player()) {
          return true;
        }
        // we are not done yet or the color was our own.
        return false;
      }
    }
    break;
  }
  case PieceType::KNIGHT: {
    // simply check the to location for opponent color
    auto it = m_board.find(move.to());
    if (it != m_board.cend()) {
      return (it->second.color() != move.player());
    } else {
      return true;
    }
    break;
  }
  case PieceType::ROOK: {
    // start from center and go outwards
    int i = move.from().row();
    int j = move.from().col();

    int next_i = (move.to().row() - move.from().row()) != 0
                     ? (move.to().row() - move.from().row()) /
                           std::abs(move.to().row() - move.from().row())
                     : 0;
    int next_j = (move.to().col() - move.from().col()) != 0
                     ? (move.to().col() - move.from().col()) /
                           std::abs(move.to().col() - move.from().col())
                     : 0;

    while (Position(i, j) != move.to()) {
      i += next_i;
      j += next_j;
      auto it = m_board.find(Position(i, j));
      if (it != m_board.cend()) {
        // if we are at the desired location, and the piece is of opponent
        // color, the move is valid
        if (Position(i, j) == move.to() &&
            it->second.color() != move.player()) {
          return true;
        }
        // we are not done yet or the color was our own.
        return false;
      }
    }
    break;
  }
  case PieceType::QUEEN: {
    // create new moves (corresponding of rook and bishop) and test both
    Move m1 = Move(move.player(), PieceType::BISHOP, move.from(), move.to());
    Move m2 = Move(move.player(), PieceType::ROOK, move.from(), move.to());
    return isValid(m1) || isValid(m2);
    break;
  }
  case PieceType::KING: {
    // for castling: check for certain fields
    if (move.player() == PlayerColor::WHITE) {
      if (move.from() == Position(0, 4) && move.to() == Position(0, 6)) {
        // check for empty fields
        return !(hasPiece(Position(0, 5)) || hasPiece(Position(0, 6)));
      }
      if (move.from() == Position(0, 4) && move.to() == Position(0, 2)) {
        return !(hasPiece(Position(0, 2)) || hasPiece(Position(0, 3)));
      }
    } else {
      if (move.from() == Position(7, 4) && move.to() == Position(7, 6)) {
        return !(hasPiece(Position(0, 5)) || hasPiece(Position(0, 6)));
      }
      if (move.from() == Position(7, 4) && move.to() == Position(7, 2)) {
        return !(hasPiece(Position(0, 2)) || hasPiece(Position(0, 3)));
      }
    }

    auto it = m_board.find(move.to());
    if (it != m_board.cend()) {
      return it->second.color() != move.player();
    } else {
      return true;
    }
    break;
  }
  }

  // in all other cases: return true (since the move must be valid in order to
  // get here)
  return true;
}

bool Board::isAttackMove(const Move &move) const {
  if (!isValid(move)) {
    throw std::runtime_error("This move is not valid.");
  }

  auto it = m_board.find(move.to());
  if (it == m_board.cend()) {
    // check if a pawn is one further (en-passant)

    if (move.piece() == PieceType::PAWN) {
      if (move.player() == PlayerColor::WHITE) {
        auto it2 = m_board.find(Position(move.to().row() - 1, move.to().col()));
        if (it2 != m_board.cend()) {
          return it2->second.type() == PieceType::PAWN &&
                 it2->second.color() == PlayerColor::BLACK;
        } else {
          return false;
        }
      } else {
        auto it2 = m_board.find(Position(move.to().row() + 1, move.to().col()));
        if (it2 != m_board.cend()) {
          return it2->second.type() == PieceType::PAWN &&
                 it2->second.color() == PlayerColor::WHITE;
        } else {
          return false;
        }
      }
      // no piece is there
      return false;
    }
  } else {
    return it->second.color() != move.player();
  }
  return false;
}

bool Board::isCheckMove(const Move &move) const {
  if (!isValid(move)) {
    throw std::runtime_error("This move is not valid.");
  }

  auto it = m_board.find(move.to());
  if (it != m_board.cend()) {
    return (it->second.color() != move.player()) &&
           it->second.type() == PieceType::KING;
  }
  return false;
}

void Board::getCheckInfo(bool &whiteCheck, bool &blackCheck) const {
  // find a king
  Position whitePos(0, 0);
  Position blackPos(0, 0);

  whiteCheck = false;
  blackCheck = false;

  for (auto it = m_board.begin(); it != m_board.end(); it++) {
    if (it->second.type() == PieceType::KING) {
      if (it->second.color() == PlayerColor::WHITE) {
        whitePos = it->first;
      } else {
        blackPos = it->first;
      }
    }
  }

  // iterate over all pieces in the field, get all valid moves from them and
  // check if a check move can be performed to the king
  for (auto it = m_board.begin(); it != m_board.end(); it++) {
    if (it->second.color() == PlayerColor::WHITE) {
      // if we already found a hit, continue
      if (blackCheck)
        continue;
      // check against black king
      Move m = Move(PlayerColor::WHITE, it->second.type(), it->first, blackPos);
      try {
        if (isCheckMove(m)) {
          blackCheck = true;
        }
      } catch (std::runtime_error) {
      }
    } else {
      // check against white king
      if (whiteCheck)
        continue;
      Move m = Move(PlayerColor::BLACK, it->second.type(), it->first, whitePos);
      try {
        if (isCheckMove(m)) {
          whiteCheck = true;
        }
      } catch (std::runtime_error) {
      }
    }
  }
}

bool Board::hasPiece(const Position &position) const {
  return m_board.find(position) != m_board.cend();
}