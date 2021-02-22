#include <chessEngine/ai.h>
#include <chessEngine/io.h>
#include <omp.h>

using namespace chessEngine;

AI::AI(const GameState *game) { m_game = new GameState(*game); }

AI::~AI() { delete m_game; }

Move AI::getBestNextMove() {
  return Move(m_game->getNextPlayer(), PieceType::ROOK, Position(0, 0),
              Position(0, 0));
}

int AI::countRecursive(int depth, GameState state) {
  if (depth == 0) {
    return 1;
  }

  PlayerColor nextPlayer = state.getNextPlayer();

  // get all valid moves for the next player
  std::vector<Move> validMoves = state.getAllValidMovesForPlayer(nextPlayer);

  int sum = 0;

  // TODO: promotion move should be done 4 times (for each piece).

#pragma omp parallel for reduction(+ : sum)
  for (auto move_it = validMoves.begin(); move_it != validMoves.end();
       ++move_it) {
    GameState myState = GameState(state);
    // apply the move
    myState.applyMove(*move_it);
    sum += countRecursive(depth - 1, GameState(myState)); // recursive call.
  }

  return sum;
}

int AI::enumerateAllMoves(int depth) {
  return countRecursive(depth, GameState(*m_game));
}
