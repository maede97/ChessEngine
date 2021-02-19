#include <chessEngine/io.h>
#include <gtest/gtest.h>

using namespace chessEngine;

TEST(IO, ForsythEdwardsEmpty) {
  // no pieces on board, white next, no castling, no en-passant, no half-move,
  // initial full-move
  GameState state = IO::fromForsythEdwards("8/8/8/8/8/8/8/8 w - - 0 1");

  EXPECT_EQ(state.getBoard().numPieces(), 0);
}

TEST(IO, ForsythEdwardsDefault) {
  GameState state = IO::fromForsythEdwards(
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

  EXPECT_EQ(state.getBoard().numPieces(), 32);

  EXPECT_EQ(state.getBoard(), Board::defaultBoard());

  // TODO test further information
}

TEST(IO, ForsythEdwardsCustom) {
  GameState state = IO::fromForsythEdwards("P2P3P/8/8/8/8/8/8/8 w KQkq - 0 1");
  Piece p = Piece(PieceType::PAWN, PlayerColor::WHITE);
  EXPECT_EQ(state.getBoard().getPiece(Position(7, 0)), p);
  EXPECT_EQ(state.getBoard().getPiece(Position(7, 3)), p);
  EXPECT_EQ(state.getBoard().getPiece(Position(7, 7)), p);
}