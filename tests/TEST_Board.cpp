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
