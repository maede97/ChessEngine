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

TEST(Move, ValidityPawn) {
  for (int col = 0; col < 8; col++) {
    for (int row = 0; row < 8; row++) {
      if (row < 7) {
        // Forward move
        EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::PAWN,
                         Position(row, col), Position(row + 1, col))
                        .isValid());
        EXPECT_TRUE(Move(PlayerColor::BLACK, PieceType::PAWN,
                         Position(7 - row, col), Position(7 - row - 1, col))
                        .isValid());

        // backwards move
        EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::PAWN,
                          Position(row + 1, col), Position(row, col))
                         .isValid());
        EXPECT_FALSE(Move(PlayerColor::BLACK, PieceType::PAWN,
                          Position(7 - row - 1, col), Position(7 - row, col))
                         .isValid());
      }

      // double move only at start
      if (row == 1) {
        EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::PAWN,
                         Position(row, col), Position(row + 2, col))
                        .isValid());
        EXPECT_TRUE(Move(PlayerColor::BLACK, PieceType::PAWN,
                         Position(7 - row, col), Position(7 - row - 2, col))
                        .isValid());
      } else if (row < 6) {
        EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::PAWN,
                          Position(row, col), Position(row + 2, col))
                         .isValid());
        EXPECT_FALSE(Move(PlayerColor::BLACK, PieceType::PAWN,
                          Position(7 - row, col), Position(7 - row - 2, col))
                         .isValid());
      }

      // test attacks
      if (col > 0 && col < 7 && row < 7) {
        // forward attack
        EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::PAWN,
                         Position(row, col), Position(row + 1, col + 1))
                        .isValid(true));
        EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::PAWN,
                         Position(row, col), Position(row + 1, col - 1))
                        .isValid(true));
        EXPECT_TRUE(Move(PlayerColor::BLACK, PieceType::PAWN,
                         Position(7 - row, col), Position(7 - row - 1, col + 1))
                        .isValid(true));
        EXPECT_TRUE(Move(PlayerColor::BLACK, PieceType::PAWN,
                         Position(7 - row, col), Position(7 - row - 1, col - 1))
                        .isValid(true));
        // backwards attack
        EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::PAWN,
                          Position(row + 1, col), Position(row, col + 1))
                         .isValid(true));
        EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::PAWN,
                          Position(row + 1, col), Position(row, col - 1))
                         .isValid(true));
        EXPECT_FALSE(Move(PlayerColor::BLACK, PieceType::PAWN,
                          Position(7 - row - 1, col),
                          Position(7 - row, col + 1))
                         .isValid(true));
        EXPECT_FALSE(Move(PlayerColor::BLACK, PieceType::PAWN,
                          Position(7 - row - 1, col),
                          Position(7 - row, col - 1))
                         .isValid(true));
      }
    }
  }
}

TEST(Move, ValidityBishop) {
  // only diagonal moves are allowed
}

// TODO write all remaining test cases (Knight, Rook, Queen, King)