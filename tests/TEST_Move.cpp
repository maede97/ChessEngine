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
  for (int i = 1; i < 8; i++) {
    // check diagonal 1
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::BISHOP, Position(0, 0),
                     Position(i, i))
                    .isValid());
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::BISHOP, Position(7, 7),
                     Position(7 - i, 7 - i))
                    .isValid());

    // check diagonal 2
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::BISHOP, Position(0, 7),
                     Position(i, 7 - i))
                    .isValid());
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::BISHOP, Position(7, 0),
                     Position(7 - i, i))
                    .isValid());

    // check straight 1
    EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::BISHOP, Position(0, 0),
                      Position(i, 0))
                     .isValid());
    EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::BISHOP, Position(7, 0),
                      Position(7 - i, 0))
                     .isValid());
    // check straight 2
    EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::BISHOP, Position(0, 0),
                      Position(0, i))
                     .isValid());
    EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::BISHOP, Position(0, 7),
                      Position(0, 7 - i))
                     .isValid());
  }
}

TEST(Move, ValidityKnight) {
  // for the knight, we take a position in the middle and test all positions
  // around.
  Position pos = Position(2, 2);
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(0, 0))
                   .isValid());
  EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(0, 1))
                  .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(0, 2))
                   .isValid());
  EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(0, 3))
                  .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(0, 4))
                   .isValid());
  EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(1, 0))
                  .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(1, 1))
                   .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(1, 2))
                   .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(1, 3))
                   .isValid());
  EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(1, 4))
                  .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(2, 0))
                   .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(2, 1))
                   .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(2, 3))
                   .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(2, 4))
                   .isValid());
  EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(3, 0))
                  .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(3, 1))
                   .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(3, 2))
                   .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(3, 3))
                   .isValid());
  EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(3, 4))
                  .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(4, 0))
                   .isValid());
  EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(4, 1))
                  .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(4, 2))
                   .isValid());
  EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(4, 3))
                  .isValid());
  EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::KNIGHT, pos, Position(4, 4))
                   .isValid());
}

TEST(Move, ValidityRook) {
  // only diagonal moves are allowed
  for (int i = 1; i < 8; i++) {
    // check diagonal 1
    EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::ROOK, Position(0, 0),
                      Position(i, i))
                     .isValid());
    EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::ROOK, Position(7, 7),
                      Position(7 - i, 7 - i))
                     .isValid());

    // check diagonal 2
    EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::ROOK, Position(0, 7),
                      Position(i, 7 - i))
                     .isValid());
    EXPECT_FALSE(Move(PlayerColor::WHITE, PieceType::ROOK, Position(7, 0),
                      Position(7 - i, i))
                     .isValid());

    // check straight 1
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::ROOK, Position(0, 0),
                     Position(i, 0))
                    .isValid());
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::ROOK, Position(7, 0),
                     Position(7 - i, 0))
                    .isValid());
    // check straight 2
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::ROOK, Position(0, 0),
                     Position(0, i))
                    .isValid());
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::ROOK, Position(0, 7),
                     Position(0, 7 - i))
                    .isValid());
  }
}

TEST(Move, ValidityQueen) {
  // test all from the rook and the bishop
  for (int i = 1; i < 8; i++) {
    // check diagonal 1
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::QUEEN, Position(0, 0),
                     Position(i, i))
                    .isValid());
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::QUEEN, Position(7, 7),
                     Position(7 - i, 7 - i))
                    .isValid());

    // check diagonal 2
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::QUEEN, Position(0, 7),
                     Position(i, 7 - i))
                    .isValid());
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::QUEEN, Position(7, 0),
                     Position(7 - i, i))
                    .isValid());

    // check straight 1
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::QUEEN, Position(0, 0),
                     Position(i, 0))
                    .isValid());
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::QUEEN, Position(7, 0),
                     Position(7 - i, 0))
                    .isValid());
    // check straight 2
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::QUEEN, Position(0, 0),
                     Position(0, i))
                    .isValid());
    EXPECT_TRUE(Move(PlayerColor::WHITE, PieceType::QUEEN, Position(0, 7),
                     Position(0, 7 - i))
                    .isValid());
  }

  // some special picks to verify the correctness
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::QUEEN, Position(0, 0), Position(3, 2))
          .isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::QUEEN, Position(0, 0), Position(2, 3))
          .isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::QUEEN, Position(7, 2), Position(1, 4))
          .isValid());
}

TEST(Move, ValidityKing) {
  Position pos = Position(2, 2);
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(0, 0)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(0, 1)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(0, 2)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(0, 3)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(0, 4)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(1, 0)).isValid());
  EXPECT_TRUE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(1, 1)).isValid());
  EXPECT_TRUE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(1, 2)).isValid());
  EXPECT_TRUE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(1, 3)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(1, 4)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(2, 0)).isValid());
  EXPECT_TRUE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(2, 1)).isValid());
  EXPECT_TRUE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(2, 3)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(2, 4)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(3, 0)).isValid());
  EXPECT_TRUE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(3, 1)).isValid());
  EXPECT_TRUE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(3, 2)).isValid());
  EXPECT_TRUE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(3, 3)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(3, 4)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(4, 0)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(4, 1)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(4, 2)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(4, 3)).isValid());
  EXPECT_FALSE(
      Move(PlayerColor::WHITE, PieceType::KING, pos, Position(4, 4)).isValid());
}