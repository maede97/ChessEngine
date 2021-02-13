#pragma once

#include <unordered_map>
#include <chessEngine/piece.h>
#include <chessEngine/position.h>

// forward declaration of IO class for friend
class IO;

struct KeyHash
{
    std::size_t operator()(const Position &k) const
    {
        return k.hash();
    }
};

struct KeyEqual
{
    bool operator()(const Position &lhs, const Position &rhs) const
    {
        return lhs.hash() == rhs.hash();
    }
};

class Board
{
public:
    using map_t = std::unordered_map<Position, Piece, KeyHash, KeyEqual>;

    static Board defaultBoard();
    static Board emptyBoard();

    Board() = delete;
    // create a board by a given position map
    Board(map_t positions);

private:
    friend IO;
    map_t m_board;
};