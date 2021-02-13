#include <gtest/gtest.h>
#include <chessEngine/definitions.h>

/**
 * This file contains unit tests for all possible types in the library.
 */

TEST(Types, Pieces) {
    ASSERT_EQ((int)PieceType::PAWN, 1);
    ASSERT_EQ((int)PieceType::KNIGHT, 2);
    ASSERT_EQ((int)PieceType::BISHOP, 3);
    ASSERT_EQ((int)PieceType::ROOK, 4);
    ASSERT_EQ((int)PieceType::QUEEN, 5);
    ASSERT_EQ((int)PieceType::KING, 6);
}

TEST(Types, Color) {
    ASSERT_EQ((int)PlayerColor::WHITE, 1);
    ASSERT_EQ((int)PlayerColor::BLACK, 2);
}