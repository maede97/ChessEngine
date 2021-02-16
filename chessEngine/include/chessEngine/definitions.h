#pragma once
#include <string>

namespace chessEngine
{
    /**
     * @brief Enum which stores all possible player colors.
     */
    enum class PlayerColor
    {
        WHITE = 1, ///< w
        BLACK = 2 ///< b
    };

    /**
     * @brief Enum which stores all possible piece types.
     */
    enum class PieceType
    {
        PAWN = 1, ///< P
        KNIGHT = 2, ///< N
        BISHOP = 3, ///< B
        ROOK = 4, ///< R
        QUEEN = 5, ///< Q
        KING = 6 ///< K
    };

} // namespace chessEngine