#include <gtest/gtest.h>
#include <chessEngine/position.h>

TEST(Position, Constructor)
{
    auto p = Position(0, 0);
}

TEST(Position, ConstructorOutOfBounds)
{
    try
    {
        auto p = Position(8, 8);
        // We should have the fail above. So fail now.
        FAIL();
    }
    catch (std::runtime_error e)
    {
        EXPECT_STREQ(e.what(), "Row or column out of bounds.");
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