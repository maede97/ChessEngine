#pragma once

#include <chessEngine/board.h>

/**
 * This class contains various helpers to read/write chess boards
 */
class IO
{
public:
    static Board fromForsythEdwards(const char * string);
};