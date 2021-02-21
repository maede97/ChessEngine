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

void GameState::getCastleInformation(bool &whiteKingSide, bool &whiteQueenSide,
                                     bool &blackKingSide,
                                     bool &blackQueenSide) const {
  whiteKingSide = m_whiteCastleKingSide;
  whiteQueenSide = m_whiteCastleQueenSide;
  blackKingSide = m_blackCastleKingSide;
  blackQueenSide = m_blackCastleQueenSide;
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

    // check for castling
    // TODO check if this castle move would make this person checked.
    if (move.piece() == PieceType::KING) {
      if (m_nextPlayer == PlayerColor::WHITE) {
        if (m_whiteCastleKingSide) {
          if (move.from() == Position(0, 4) && move.to() == Position(0, 6))
            return true;
        }
        if (m_whiteCastleQueenSide) {
          if (move.from() == Position(0, 4) && move.to() == Position(0, 2))
            return true;
        }
      } else {
        if (m_blackCastleKingSide) {
          if (move.from() == Position(7, 4) && move.to() == Position(7, 6))
            return true;
        }
        if (m_blackCastleQueenSide) {
          if (move.from() == Position(7, 4) && move.to() == Position(7, 2))
            return true;
        }
      }
    }

    // TODO check for en-passant

    return true; // for now.
  } else {
    return false;
  }
}

void GameState::applyMove(const Move &move) {

  if (!isValid(move)) {
    throw std::runtime_error("This move is not valid.");
  }

  // check if this is an castling move, if it is, board.applyMove can not be
  // used.
  bool isCastlingMove = false;
  bool isCastlingMoveKingWhite = false;
  bool isCastlingMoveQueenWhite = false;
  bool isCastlingMoveKingBlack = false;
  bool isCastlingMoveQueenBlack = false;

  if (move.piece() == PieceType::KING) {
    if (m_nextPlayer == PlayerColor::WHITE) {
      if (m_whiteCastleKingSide) {
        if (move.from() == Position(0, 4) && move.to() == Position(0, 6))
          isCastlingMoveKingWhite = true;
      }
      if (m_whiteCastleQueenSide) {
        if (move.from() == Position(0, 4) && move.to() == Position(0, 2))
          isCastlingMoveQueenWhite = true;
      }
    } else {
      if (m_blackCastleKingSide) {
        if (move.from() == Position(7, 4) && move.to() == Position(7, 6))
          isCastlingMoveKingBlack = true;
      }
      if (m_blackCastleQueenSide) {
        if (move.from() == Position(7, 4) && move.to() == Position(7, 2))
          isCastlingMoveQueenBlack = true;
      }
    }
  }

  // if we came all the way down to here, the move is valid and can be played.
  m_board.applyMove(move);

  isCastlingMove = isCastlingMoveKingWhite || isCastlingMoveQueenWhite ||
                   isCastlingMoveKingBlack || isCastlingMoveQueenBlack;
  if (isCastlingMove) {
    // remove the rook and replace it.
    if (isCastlingMoveKingWhite) {
      m_board.removePiece(Position(0, 7));
      m_board.placePiece(Position(0, 5),
                         Piece(PlayerColor::WHITE, PieceType::ROOK));
      m_whiteCastleKingSide = false;
      m_whiteCastleQueenSide = false;
    } else if (isCastlingMoveQueenWhite) {
      m_board.removePiece(Position(0, 0));
      m_board.placePiece(Position(0, 3),
                         Piece(PlayerColor::WHITE, PieceType::ROOK));
      m_whiteCastleKingSide = false;
      m_whiteCastleQueenSide = false;
    } else if (isCastlingMoveKingBlack) {
      m_board.removePiece(Position(7, 7));
      m_board.placePiece(Position(7, 5),
                         Piece(PlayerColor::BLACK, PieceType::ROOK));
      m_blackCastleKingSide = false;
      m_blackCastleQueenSide = false;
    } else if (isCastlingMoveQueenBlack) {
      m_board.removePiece(Position(7, 0));
      m_board.placePiece(Position(7, 3),
                         Piece(PlayerColor::BLACK, PieceType::ROOK));
      m_blackCastleKingSide = false;
      m_blackCastleQueenSide = false;
    }
  } else {
    // check if it was a rook or a king
    if (move.piece() == PieceType::KING) {
      if (move.player() == PlayerColor::WHITE) {
        m_whiteCastleKingSide = false;
        m_whiteCastleQueenSide = false;
      } else {
        m_blackCastleKingSide = false;
        m_blackCastleQueenSide = false;
      }
    } else if (move.piece() == PieceType::ROOK) {
      if (move.player() == PlayerColor::WHITE) {
        if (m_whiteCastleKingSide && move.from() == Position(0, 7))
          m_whiteCastleKingSide = false;
        if (m_whiteCastleQueenSide && move.from() == Position(0, 0))
          m_whiteCastleQueenSide = false;
      } else {
        if (m_blackCastleKingSide && move.from() == Position(7, 7))
          m_blackCastleKingSide = false;
        if (m_blackCastleQueenSide && move.from() == Position(7, 0))
          m_blackCastleQueenSide = false;
      }
    }
  }

  // switch next player
  m_nextPlayer = (m_nextPlayer == PlayerColor::WHITE) ? PlayerColor::BLACK
                                                      : PlayerColor::WHITE;

  // TODO: update counts (halfmoves)
  // TODO: add captured pieces to vectors

  // 1. check if this move is a castling move.

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