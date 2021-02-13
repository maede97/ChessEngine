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