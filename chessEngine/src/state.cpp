#include <chessEngine/state.h>

using namespace chessEngine;

GameState::GameState() : m_board(Board::defaultBoard()) {}

void GameState::setBoard(const Board &board) { m_board = board; }

Board GameState::getBoard() const { return m_board; }