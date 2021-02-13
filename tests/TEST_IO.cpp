#include <gtest/gtest.h>
#include <chessEngine/io.h>

TEST(IO, ForsythEdwardsEmpty)
{
    // no pieces on board, white next, no castling, no en-passant, no half-move, initial full-move
    Board b = IO::fromForsythEdwards("8/8/8/8/8/8/8/8 w - - 0 1");

    // TODO
}