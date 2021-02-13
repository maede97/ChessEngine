#include <chessEngine/position.h>
#include <stdexcept>

Position::Position(uint8_t row, uint8_t column)
{
    // sanity checks
    if (row < 0 || column < 0 || row > 7 || column > 7)
    {
        throw std::runtime_error("Row or column out of bounds.");
    }

    m_internal_position = row;
}