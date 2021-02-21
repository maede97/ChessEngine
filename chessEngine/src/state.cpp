#include <chessEngine/state.h>

using namespace chessEngine;

GameState::GameState()
    : m_board(Board::defaultBoard()), m_nextPlayer(PlayerColor::WHITE) {}

void GameState::setBoard(const Board &board) { m_board = board; }

Board GameState::getBoard() const { return m_board; }

void GameState::setNextPlayer(PlayerColor color) { m_nextPlayer = color; }

PlayerColor GameState::getNextPlayer() const { return m_nextPlayer; }

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

bool GameState::isValid(const Move &move) const {
  // check for the correct player
  if (m_nextPlayer != move.player()) {
    return false;
  }
  if (m_board.isValid(move)) {
    bool whiteCheck;
    bool blackCheck;
    m_board.getCheckInfo(whiteCheck, blackCheck);

    if (m_nextPlayer == PlayerColor::WHITE) {
      if (whiteCheck) {
        // TODO: check if this move finishes check.
      } else {
        // TODO: check if this move would make white checked.
      }
    } else {
      if (blackCheck) {
        // TODO: check if this move finishes check.
      } else {
        // TODO: check if this move would make black checked.
      }
    }

    return true; // for now.
  } else {
    return false;
  }
}

void GameState::applyMove(const Move &move) {

  if (!isValid(move)) {
    throw std::runtime_error("This move is not valid.");
  }

  // if we came all the way down to here, the move is valid and can be played.
  m_board.applyMove(move);
  // switch next player
  m_nextPlayer = (m_nextPlayer == PlayerColor::WHITE) ? PlayerColor::BLACK
                                                      : PlayerColor::WHITE;

  // TODO: update counts (halfmoves)
  // TODO: add captured pieces to vectors

  // increase full moves
  if (m_nextPlayer == PlayerColor::WHITE) {
    m_fullMoves++;
  }
}

std::vector<std::vector<bool>>
GameState::getValidMoves(const Position &position) const {

  // get all valid moves from the board and remove those, who do not work

  // for now: return board moves
  return m_board.getValidMoves(position);
}