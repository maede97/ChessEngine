#include <chessEngine/move.h>

using namespace chessEngine;

Move::Move(PlayerColor player, PieceType piece, Position from, Position to)
    : m_player(player), m_piece(piece), m_from(from), m_to(to) {}

PlayerColor Move::player() const { return m_player; }
PieceType Move::piece() const { return m_piece; }
Position Move::from() const { return m_from; }
Position Move::to() const { return m_to; }

PlayerColor &Move::player() { return m_player; }
PieceType &Move::piece() { return m_piece; }
Position &Move::from() { return m_from; }
Position &Move::to() { return m_to; }

bool Move::isValid(bool attack) const {
  // if we stay on the same piece, this is not a valid move.
  if (m_to == m_from)
    return false;

  switch (m_piece) {
  case PieceType::PAWN: {
    // if white, can only move towards positive row count
    // if black, can only move towards negative row count
    // then check for distance: should be between 1 and 2 (only if from initial
    // line)
    if (m_player == PlayerColor::WHITE) {
      if (m_to.row() <= m_from.row())
        return false;
      if (m_from.row() == 1) {
        // move can be 1 or 2
        if (m_to.row() - m_from.row() > 2)
          return false;
      } else {
        // move must be 1
        if (m_to.row() - m_from.row() != 1)
          return false;
      }
    } else {
      // black
      if (m_from.row() <= m_to.row())
        return false;
      if (m_from.row() == 6) {
        // move can be 1 or 2
        if (m_from.row() - m_to.row() > 2)
          return false;
      } else {
        // move must be 1
        if (m_from.row() - m_to.row() != 1)
          return false;
      }
    }

    // check for attack
    if (attack) {
      // col must change by one
      if (std::abs(m_from.col() - m_to.col()) != 1)
        return false;
    } else {
      // col must stay
      if (m_from.col() != m_to.col())
        return false;
    }

    break;
  }
  case PieceType::BISHOP: {
    // this piece can only move diagonally
    // require that both axis change the same
    if (std::abs(m_from.row() - m_to.row()) !=
        std::abs(m_from.col() - m_to.col()))
      return false;
    break;
  }
  case PieceType::KNIGHT: {
    // two cases:
    // 1. change of 1 in row, change of 2 in columns
    // 2. change of 2 in row, change of 1 in columns

    bool case1 = std::abs(m_from.row() - m_to.row()) == 1 &&
                 std::abs(m_from.col() - m_to.col()) == 2;
    bool case2 = std::abs(m_from.row() - m_to.row()) == 2 &&
                 std::abs(m_from.col() - m_to.col()) == 1;

    bool true_if = case1 && !case2 || case2 && !case1;

    if (!true_if)
      return false;

    break;
  }
  case PieceType::ROOK: {
    // two cases:
    // 1. change only in rows
    // 2. change only in cols

    bool case1 = std::abs(m_from.row() - m_to.row()) > 0 &&
                 std::abs(m_from.col() - m_to.col()) == 0;
    bool case2 = std::abs(m_from.row() - m_to.row()) == 0 &&
                 std::abs(m_from.col() - m_to.col()) > 0;

    bool true_if = case1 && !case2 || case2 && !case1;

    if (!true_if)
      return false;

    break;
  }
  case PieceType::QUEEN: {

    // 3 cases
    // 1. change only in rows
    // 2. change only in cols
    // 3. diagonally
    bool case1 = std::abs(m_from.row() - m_to.row()) > 0 &&
                 std::abs(m_from.col() - m_to.col()) == 0;
    bool case2 = std::abs(m_from.row() - m_to.row()) == 0 &&
                 std::abs(m_from.col() - m_to.col()) > 0;
    bool case3 = std::abs(m_from.row() - m_to.row()) ==
                 std::abs(m_from.col() - m_to.col());

    bool true_if = case1 && !case2 && !case3 || !case1 && case2 && !case3 ||
                   !case1 && !case2 && case3;

    if (!true_if)
      return false;

    break;
  }
  case PieceType::KING: {
    // valid in two cases:
    // 1. rook with length 1
    // 2. bishop with length 1

    // rook can be expressed in 2 conditions, resulting in 3
    bool case1 = std::abs(m_from.row() - m_to.row()) == 1 &&
                 std::abs(m_from.col() - m_to.col()) == 0;
    bool case2 = std::abs(m_from.row() - m_to.row()) == 0 &&
                 std::abs(m_from.col() - m_to.col()) == 1;
    bool case3 = std::abs(m_from.row() - m_to.row()) ==
                     std::abs(m_from.col() - m_to.col()) &&
                 std::abs(m_from.row() - m_to.row()) == 1;

    bool true_if = case1 && !case2 && !case3 || !case1 && case2 && !case3 ||
                   !case1 && !case2 && case3;

    if (!true_if)
      return false;

    break;
  }
  }

  // all seems good, return true
  return true;
}