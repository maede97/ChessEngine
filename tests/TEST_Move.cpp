#include <gtest/gtest.h>
#include <chessEngine/move.h>
using namespace chessEngine;
TEST(Move, Constructor)
{
    auto m = Move(PlayerColor::WHITE, PieceType::PAWN, Position(0, 0), Position(1, 0));
}