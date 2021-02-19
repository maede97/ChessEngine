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

TEST(Piece, Comparisons) {
  auto p1 = Piece(PieceType::PAWN, PlayerColor::WHITE);
  auto p2 = Piece(PieceType::PAWN, PlayerColor::WHITE);
  auto p3 = Piece(PieceType::PAWN, PlayerColor::BLACK);
  auto p4 = Piece(PieceType::KNIGHT, PlayerColor::WHITE);

  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p2, p1);

  EXPECT_NE(p1, p3);
  EXPECT_NE(p3, p1);

  EXPECT_NE(p1, p4);
  EXPECT_NE(p4, p1);

  EXPECT_NE(p3, p4);
  EXPECT_NE(p4, p3);
}