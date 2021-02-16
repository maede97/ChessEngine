#pragma once

#include <inttypes.h>

namespace chessEngine
{
    /**
 * Class which holds information about a position on the board.
 */
    class Position
    {

    public:
        Position() = delete;

        Position(uint8_t row, uint8_t col);

        uint8_t row() const;
        uint8_t col() const;

        void get(uint8_t &row, uint8_t &column) const;

        // make the internal representation public, such that this can be used as a key for a hashmap
        uint8_t hash() const;

    private:
        // 6 bits are enough to represent every position on the board
        // however, in C++, the smallest type is 8 bits, therefore we use this
        uint8_t m_internal_position;
    };

} // namespace chessEngine