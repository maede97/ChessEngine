#include <chessEngine/state.h>
#include <chessEngine/ai.h>
#include <iostream>

using namespace chessEngine;
int main(int argc, char const *argv[]) {

  GameState game;

  AI ai(&game);

  std::cout << ai.enumerateAllMoves(5) << std::endl;

  return 0;
}
