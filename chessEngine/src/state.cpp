#include <chessEngine/state.h>

using namespace chessEngine;

GameState::GameState() : m_board(Board::defaultBoard()) {}

void GameState::setBoard(const Board &board) { m_board = board; }

Board GameState::getBoard() const { return m_board; }

void GameState::setNextPlayer(PlayerColor color) { m_nextPlayer = color; }

void GameState::setCastleInformation(bool whiteKingSide, bool whiteQueenSide,
                                     bool blackKingSide, bool blackQueenSide) {
  m_whiteCastleKingSide = whiteKingSide;
  m_whiteCastleQueenSide = whiteQueenSide;
  m_blackCastleKingSide = blackKingSide;
  m_blackCastleQueenSide = blackQueenSide;
}

void GameState::setHalfMoves(unsigned int halfMoves) {
  m_halfMoves = halfMoves;
}
void GameState::setFullMoves(unsigned int fullMoves) {
  if (fullMoves < 1) {
    throw std::runtime_error("Full Moves must be at least 1.");
  }
  m_fullMoves = fullMoves;
}