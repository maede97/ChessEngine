#pragma once

#include <inttypes.h>

namespace chessEngine
{
    /**
     * @brief This class helds information about a single position on the Board.
     */
    class Position
    {

    public:
        /**
         * @brief We do not allow the default constructor.
         */
        Position() = delete;
        /**
         * @brief Constructs a position from a given row and column.
         * @param row The row, starting from 0 (top) to 7 (bottom).
         * @param column The column, starting from 0 (left) to 7 (right).
         * @throws std::runtime_error if the indices are out of bounds.
         */
        Position(uint8_t row, uint8_t col);

        /**
         * @brief Getter for the row
         */
        uint8_t row() const;
        /**
         * @brief Getter for the column
         */
        uint8_t col() const;

        /**
         * @brief Getter for row and column.
         * @param row Where to write the row.
         * @param column Where to write the column.
         */
        void get(uint8_t &row, uint8_t &column) const;

        /**
         * @brief A hash of the current position, which is unique for each position on the board.
         * @return The hash value (8 bits suffice for 64 positions).
         */
        uint8_t hash() const;

    private:
        /**
         * @brief The internal position store.
         * 6 bits are enough to represent every position on the board
         * however, in C++, the smallest type is 8 bits, therefore we use this
         */
        uint8_t m_internal_position;
    };

} // namespace chessEngine