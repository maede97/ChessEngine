#include <chessEngine/move.h>
#include <gtest/gtest.h>
using namespace chessEngine;
TEST(Move, Constructor) {
  auto m =
      Move(PlayerColor::WHITE, PieceType::PAWN, Position(0, 0), Position(1, 0));
}