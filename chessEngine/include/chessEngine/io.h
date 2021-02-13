#pragma once

#include <chessEngine/board.h>

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
     * Write a board to the console.
     * @param invertColors If you are in a terminal with dark background, you might want to invert the colors by setting this flag to true.
     */
    static void writeBoardToConsole(const Board &board, bool invertColors = false);
};