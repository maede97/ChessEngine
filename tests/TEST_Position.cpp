#include <chessEngine/position.h>
#include <gtest/gtest.h>
using namespace chessEngine;
TEST(Position, Constructor) { auto p = Position(0, 0); }

TEST(Position, ConstructorOutOfBounds)
{
  try
  {
    auto p = Position(8, 8);
    // We should have the fail above. So fail now.
    FAIL();
  }
  catch (std::out_of_range e)
  {
    EXPECT_STREQ(e.what(), "Row or column out of bounds.");
  }
  catch (std::exception)
  {
    // if we catch any other exception, we fail
    FAIL();
  }
}

TEST(Position, ValueKeeping)
{
  auto p = Position(0, 0);
  EXPECT_EQ(p.row(), 0);
  EXPECT_EQ(p.col(), 0);
}

TEST(Position, ValueKeeping2)
{
  auto p = Position(4, 5);
  EXPECT_EQ(p.row(), 4);
  EXPECT_EQ(p.col(), 5);
}

TEST(Position, Getter)
{
  auto p = Position(4, 5);
  uint8_t row, col;
  p.get(row, col);
  EXPECT_EQ(row, 4);
  EXPECT_EQ(col, 5);
}