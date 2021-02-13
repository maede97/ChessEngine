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
};