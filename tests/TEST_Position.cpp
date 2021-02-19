#include <chessEngine/position.h>
#include <gtest/gtest.h>
using namespace chessEngine;
TEST(Position, Constructor) {
  auto p = Position(0, 0);
  SUCCEED();
}

TEST(Position, ConstructorOutOfBounds) {
  EXPECT_THROW(auto p = Position(8, 8), std::out_of_range);
  EXPECT_THROW(auto p = Position(0, 8), std::out_of_range);
  EXPECT_THROW(auto p = Position(8, 0), std::out_of_range);
}

TEST(Position, ValueKeeping) {
  auto p = Position(0, 0);
  EXPECT_EQ(p.row(), 0);
  EXPECT_EQ(p.col(), 0);
}

TEST(Position, ValueKeeping2) {
  auto p = Position(4, 5);
  EXPECT_EQ(p.row(), 4);
  EXPECT_EQ(p.col(), 5);
}

TEST(Position, Getter) {
  auto p = Position(4, 5);
  uint8_t row, col;
  p.get(row, col);
  EXPECT_EQ(row, 4);
  EXPECT_EQ(col, 5);
}

TEST(Position, Comparisons) {
  auto p1 = Position(0, 0);
  auto p2 = Position(0, 0);
  auto p3 = Position(0, 1);
  auto p4 = Position(1, 0);

  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p2, p1);

  EXPECT_NE(p1, p3);
  EXPECT_NE(p3, p1);

  EXPECT_NE(p1, p4);
  EXPECT_NE(p4, p1);

  EXPECT_NE(p3, p4);
  EXPECT_NE(p4, p3);
}