#pragma once

#include <chessEngine/board.h>
#include <string>

namespace chessEngine
{

    /**
 * This class contains various helpers to read/write chess boards
 */
    class IO
    {
    public:
        /**
     * Create a board from the Forsyth-Edwards representation.
     * See https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
     */
        static Board fromForsythEdwards(const char *string);

        /**
     * Write a simpler board representation to a string.
     * @attention This eliminates the colors, it is therefore not possible to see which pieces belong to wich player!
     * @param invertColors If you are in a terminal with dark background, you might want to invert the colors by setting this flag to true.
     */
        static std::string writeBoardToString(const Board &board);

        static std::string writeWhitePiecesToString(const Board &board);
        static std::string writeBlackPiecesToString(const Board &board);

        /**
     * Write a board to the console.
     * @param invertColors If you are in a terminal with dark background, you might want to invert the colors by setting this flag to true.
     */
        static void writeBoardToConsole(const Board &board, bool invertColors = false);
    };

} // namespace chessEngine