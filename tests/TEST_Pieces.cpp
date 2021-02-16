#include <chessEngine/piece.h>
#include <gtest/gtest.h>
using namespace chessEngine;
/**
 * This file contains unit tests for the Piece class.
 */

TEST(Piece, Constructor) {
  auto p = Piece(PieceType::PAWN, PlayerColor::WHITE);
  SUCCEED();
}

TEST(Piece, SetConstructor) {
  auto p = Piece{PieceType::PAWN, PlayerColor::WHITE};
  SUCCEED();
}

TEST(Piece, Getters) {
  auto p = Piece{PieceType::PAWN, PlayerColor::WHITE};

  EXPECT_EQ(p.type(), PieceType::PAWN);
  EXPECT_EQ(p.color(), PlayerColor::WHITE);
}