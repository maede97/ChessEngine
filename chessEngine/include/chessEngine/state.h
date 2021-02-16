#pragma once
#include <chessEngine/definitions.h>
#include <chessEngine/move.h>
#include <chessEngine/board.h>

#include <vector>

class GameState
{
public:
    GameState();

private:
    std::vector<Move> m_moves; // all moves previously done
    Board m_board; // current board
};