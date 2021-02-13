#pragma once

#include <chessEngine/definitions.h>
#include <chessEngine/position.h>

/**
 * This struct contains information about a single move on the game
 */
struct Move
{
    PlayerColor player;
    Position from;
    Position to;
};