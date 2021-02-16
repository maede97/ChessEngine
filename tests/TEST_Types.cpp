#include <chessEngine/definitions.h>
#include <gtest/gtest.h>
using namespace chessEngine;
/**
 * This file contains unit tests for all possible types in the library.
 */

TEST(Types, Pieces) {
  EXPECT_EQ((int)PieceType::PAWN, 1);
  EXPECT_EQ((int)PieceType::KNIGHT, 2);
  EXPECT_EQ((int)PieceType::BISHOP, 3);
  EXPECT_EQ((int)PieceType::ROOK, 4);
  EXPECT_EQ((int)PieceType::QUEEN, 5);
  EXPECT_EQ((int)PieceType::KING, 6);
}

TEST(Types, Color) {
  EXPECT_EQ((int)PlayerColor::WHITE, 1);
  EXPECT_EQ((int)PlayerColor::BLACK, 2);
}