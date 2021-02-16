#include <chessEngine/io.h>
#include <gtest/gtest.h>
using namespace chessEngine;
TEST(IO, ForsythEdwardsEmpty) {
  // no pieces on board, white next, no castling, no en-passant, no half-move,
  // initial full-move
  Board b = IO::fromForsythEdwards("8/8/8/8/8/8/8/8 w - - 0 1");

  EXPECT_EQ(b.numPieces(), 0);
}

// TODO