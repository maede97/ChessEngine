#include <chessEngine/move.h>
#include <gtest/gtest.h>
using namespace chessEngine;
TEST(Move, Constructor) {
  auto m =
      Move(PlayerColor::WHITE, PieceType::PAWN, Position(0, 0), Position(1, 0));
  SUCCEED();
}

TEST(Move, ValueKeeping) {
  auto m =
      Move(PlayerColor::WHITE, PieceType::PAWN, Position(0, 0), Position(1, 0));
  EXPECT_EQ(m.player(), PlayerColor::WHITE);
  EXPECT_EQ(m.piece(), PieceType::PAWN);
  EXPECT_EQ(m.from(), Position(0, 0));
  EXPECT_EQ(m.to(), Position(1, 0));
}

TEST(Move, Setter) {
  auto m =
      Move(PlayerColor::WHITE, PieceType::PAWN, Position(0, 0), Position(1, 0));
  // change all variables
  m.player() = PlayerColor::BLACK;
  m.piece() = PieceType::KNIGHT;
  m.from() = Position(0, 1);
  m.to() = Position(0, 2);

  // test for new equality
  EXPECT_EQ(m.player(), PlayerColor::BLACK);
  EXPECT_EQ(m.piece(), PieceType::KNIGHT);
  EXPECT_EQ(m.from(), Position(0, 1));
  EXPECT_EQ(m.to(), Position(0, 2));
}