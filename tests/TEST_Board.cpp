#include <chessEngine/board.h>
#include <gtest/gtest.h>
using namespace chessEngine;
/**
 * This file contains unit tests for the board class.
 */

// TODO
TEST(Board, EmptyBoard) {
  auto b = Board::emptyBoard();

  EXPECT_EQ(b.numPieces(), 0);
}

TEST(Board, DefaultBoard) {
  auto b = Board::defaultBoard();
  EXPECT_EQ(b.numPieces(), 32);

  // TODO: some more tests here
}

TEST(Board, PlacePiece) {
  auto b = Board::emptyBoard();

  b.placePiece(Position(0, 0), Piece(PieceType::PAWN, PlayerColor::WHITE));
  b.placePiece(Position(0, 1), Piece(PieceType::PAWN, PlayerColor::WHITE));
  b.placePiece(Position(1, 0), Piece(PieceType::PAWN, PlayerColor::WHITE));
  b.placePiece(Position(1, 1), Piece(PieceType::PAWN, PlayerColor::WHITE));
  EXPECT_THROW(
      b.placePiece(Position(0, 0), Piece(PieceType::PAWN, PlayerColor::WHITE)),
      std::runtime_error);
  EXPECT_THROW(
      b.placePiece(Position(0, 1), Piece(PieceType::PAWN, PlayerColor::WHITE)),
      std::runtime_error);
  EXPECT_THROW(
      b.placePiece(Position(1, 0), Piece(PieceType::PAWN, PlayerColor::WHITE)),
      std::runtime_error);
  EXPECT_THROW(
      b.placePiece(Position(1, 1), Piece(PieceType::PAWN, PlayerColor::WHITE)),
      std::runtime_error);

  auto b2 = Board::defaultBoard();
  EXPECT_THROW(
      b2.placePiece(Position(0, 0), Piece(PieceType::PAWN, PlayerColor::WHITE)),
      std::runtime_error);
  EXPECT_THROW(
      b2.placePiece(Position(0, 1), Piece(PieceType::PAWN, PlayerColor::WHITE)),
      std::runtime_error);
  EXPECT_THROW(
      b2.placePiece(Position(1, 0), Piece(PieceType::PAWN, PlayerColor::WHITE)),
      std::runtime_error);
  EXPECT_THROW(
      b2.placePiece(Position(1, 1), Piece(PieceType::PAWN, PlayerColor::WHITE)),
      std::runtime_error);
  b2.placePiece(Position(2, 0), Piece(PieceType::PAWN, PlayerColor::WHITE));
}

TEST(Board, RemovePiece) {
  auto b = Board::defaultBoard();
  b.removePiece(Position(0, 0));
  b.removePiece(Position(0, 1));
  EXPECT_THROW(b.removePiece(Position(2, 0)), std::runtime_error);

  EXPECT_THROW(b.getPiece(Position(2, 0)), std::runtime_error);
}

TEST(Board, GetPiece) {
  auto b = Board::defaultBoard();
  EXPECT_EQ(b.getPiece(Position(0, 0)),
            Piece(PieceType::ROOK, PlayerColor::WHITE));
  EXPECT_EQ(b.getPiece(Position(1, 0)),
            Piece(PieceType::PAWN, PlayerColor::WHITE));

  EXPECT_EQ(b.getPiece(Position(7, 0)),
            Piece(PieceType::ROOK, PlayerColor::BLACK));
  EXPECT_EQ(b.getPiece(Position(6, 0)),
            Piece(PieceType::PAWN, PlayerColor::BLACK));
}

TEST(Board, Equality) {
  auto b1 = Board::defaultBoard();
  auto b2 = Board::defaultBoard();
  auto b3 = Board::emptyBoard();

  EXPECT_EQ(b1, b2);
  EXPECT_EQ(b2, b1);

  EXPECT_NE(b1, b3);
  EXPECT_NE(b3, b1);

  EXPECT_NE(b2, b3);
  EXPECT_NE(b3, b2);

  b1.removePiece(Position(0, 0));

  EXPECT_NE(b1, b2);
  EXPECT_NE(b2, b1);

  b2.removePiece(Position(0, 0));

  EXPECT_EQ(b1, b2);
  EXPECT_EQ(b2, b1);
}

TEST(Board, ApplyMove) {
  auto b = Board::emptyBoard();

  Move m =
      Move(PlayerColor::WHITE, PieceType::PAWN, Position(1, 0), Position(2, 0));

  EXPECT_THROW(b.applyMove(m), std::runtime_error);

  auto b2 = Board::defaultBoard();
  EXPECT_NO_THROW(b2.applyMove(m));

  EXPECT_THROW(b2.getPiece(Position(1, 0)), std::runtime_error);
  EXPECT_EQ(b2.getPiece(Position(2, 0)),
            Piece(PieceType::PAWN, PlayerColor::WHITE));

  Move m2 =
      Move(PlayerColor::WHITE, PieceType::ROOK, Position(0, 0), Position(2, 0));
  // this should not work as we move onto the same field the rook is on
  EXPECT_THROW(b2.applyMove(m2), std::runtime_error);
}