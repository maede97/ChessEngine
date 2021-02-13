#include <chessEngine/position.h>
#include <stdexcept>

Position::Position(uint8_t row, uint8_t column)
{
    // sanity checks
    if (row < 0 || column < 0 || row > 7 || column > 7)
    {
        throw std::runtime_error("Row or column out of bounds.");
    }

    m_internal_position = row * 8 + column;
}

uint8_t Position::row() const
{
    // carve out the row by removing the columns
    return m_internal_position / 8;
}

uint8_t Position::col() const
{
    return m_internal_position % 8;
}

void Position::get(uint8_t& row, uint8_t& column) const { 
    row = this->row();
    column = this->col();
}

uint8_t Position::hash() const { return m_internal_position; }