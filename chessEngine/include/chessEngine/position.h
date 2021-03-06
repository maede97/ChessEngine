#pragma once

#include <inttypes.h>
#include <iostream>

namespace chessEngine {
/**
 * @brief This class helds information about a single position on the Board.
 */
class Position {

public:
  /**
   * @brief We do not allow the default constructor.
   */
  Position() = delete;
  /**
   * @brief Constructs a position from a given row and column.
   * @param row The row, starting from 0 (top) to 7 (bottom).
   * @param column The column, starting from 0 (left) to 7 (right).
   * @throws std::out_of_range if the indices are out of bounds.
   */
  Position(uint8_t row, uint8_t column);

  /**
   * @brief Getter for the row
   */
  uint8_t row() const;

  /**
   * @brief Getter for the column
   */
  uint8_t col() const;

  /**
   * @copydoc Position::col()
   */
  uint8_t column() const;

  /**
   * @brief Getter for row and column.
   * @param row Where to write the row.
   * @param column Where to write the column.
   */
  void get(uint8_t &row, uint8_t &column) const;

  /**
   * @brief A hash of the current position, which is unique for each position on
   * the board.
   * @return The hash value (8 bits suffice for 64 positions).
   */
  uint8_t hash() const;

  /**
   * @brief Compare two positions for equality.
   * @param rhs The right hand side of the comparison.
   * @return Whether the two positions are equal.
   */
  bool operator==(const Position &rhs) const;

  /**
   * @brief Compare two positions for inequality.
   * @param rhs The right hand side of the comparison.
   * @return Whether the two positions are not equal.
   */
  bool operator!=(const Position &rhs) const;

private:
  /**
   * @brief The internal position store.
   *
   * 6 bits are enough to represent every position on the board
   * however, in C++, the smallest type is 8 bits, therefore we use this
   */
  uint8_t m_internal_position;
};

} // namespace chessEngine

/**
 * @brief Print a position to a stream.
 * @param os The stream to write to.
 * @param position The position to print.
 */
std::ostream &operator<<(std::ostream &os,
                         const chessEngine::Position &position);