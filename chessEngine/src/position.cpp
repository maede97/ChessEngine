#include <chessEngine/position.h>
#include <stdexcept>

using namespace chessEngine;

Position::Position(uint8_t row, uint8_t column) {
  // sanity checks
  if (row < 0 || column < 0 || row > 7 || column > 7) {
    throw std::out_of_range("Row or column out of bounds.");
  }

  m_internal_position = row * 8 + column;
}

uint8_t Position::row() const {
  // carve out the row by removing the columns
  return m_internal_position / 8;
}

uint8_t Position::col() const { return m_internal_position % 8; }

uint8_t Position::column() const { return col(); }

void Position::get(uint8_t &row, uint8_t &column) const {
  row = this->row();
  column = this->col();
}

uint8_t Position::hash() const { return m_internal_position; }

bool Position::operator==(const Position &rhs) const {
  return rhs.hash() == this->hash();
}

bool Position::operator!=(const Position &rhs) const {
  return !operator==(rhs);
}

std::ostream &operator<<(std::ostream &out, const Position &position) {
  out << "Pos(" << (int)position.row() << "/" << (int)position.column() << ")";
  return out;
}