#pragma once

#include <chessEngine/definitions.h>
#include <chessEngine/position.h>

/**
 * This class contains information about a single move on the game
 */
class Move
{
public:
    Move() = delete;
    Move(PlayerColor player, PieceType piece, Position from, Position to);

    PlayerColor player() const;
    PieceType piece() const;
    Position from() const;
    Position to() const;

    PlayerColor& player();
    PieceType& piece();
    Position& from();
    Position& to();

private:
    PlayerColor m_player;
    PieceType m_piece;
    Position m_from;
    Position m_to;
};