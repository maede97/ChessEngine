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
    // check for castling
    if (move.piece() == PieceType::KING) {
      if (m_nextPlayer == PlayerColor::WHITE) {
        if (move.from() == Position(0, 4) && move.to() == Position(0, 6)) {
          if (!m_whiteCastleKingSide)
            return false;
        }
        if (move.from() == Position(0, 4) && move.to() == Position(0, 2)) {
          if (!m_whiteCastleQueenSide)
            return false;
        }

        else {
          if (move.from() == Position(7, 4) && move.to() == Position(7, 6)) {
            if (!m_blackCastleKingSide)
              return false;
          }

          if (move.from() == Position(7, 4) && move.to() == Position(7, 2)) {
            if (!m_blackCastleQueenSide)
              return false;
          }
        }
      }
    }

    // filter out moves which are not en-passant
    // the board does not know this because it does not know it's temporal
    // state.
    bool removeIfEnPassant = false;

    if (m_whiteEnPassant == -1 && m_nextPlayer == PlayerColor::BLACK) {
      removeIfEnPassant = true;
    }
    if (m_blackEnPassant == -1 && m_nextPlayer == PlayerColor::WHITE) {
      removeIfEnPassant = true;
    }

    if (move.piece() == PieceType::PAWN) {
      if (m_blackEnPassant != -1 && m_nextPlayer == PlayerColor::WHITE) {
        if (m_blackEnPassant == move.to().col() && move.to().row() == 5) {
          return true;
        } else {
          removeIfEnPassant = true;
        }
      }
      if (m_whiteEnPassant != -1 && m_nextPlayer == PlayerColor::BLACK) {
        if (m_whiteEnPassant == move.to().col() && move.to().row() == 2) {
          return true;
        } else {
          removeIfEnPassant = true;
        }
      }
    }

    if (removeIfEnPassant) {
      // check for en-passant, if it is, return false.
      if (move.piece() == PieceType::PAWN) {
        // check if to location is 2 from border
        int sum = std::abs(move.from().row() - move.to().row()) +
                  std::abs(move.from().col() - move.to().col());
        if (m_nextPlayer == PlayerColor::WHITE && move.to().row() == 5) {
          // check if diagonally moved
          if (sum == 2) {
            // check for empty field there
            if (!m_board.hasPiece(move.to())) {
              // check for pawn one line before
              if (m_board.hasPiece(
                      Position(move.to().row() - 1, move.to().col()))) {
                Piece p = m_board.getPiece(
                    Position(move.to().row() - 1, move.to().col()));
                if (p.type() == PieceType::PAWN &&
                    p.color() == PlayerColor::BLACK) {
                  // this was an en-passant move, remove it
                  return false;
                }
              }
            }
          }
        } else if (m_nextPlayer == PlayerColor::BLACK && move.to().row() == 2) {
          if (sum == 2) {
            // check for empty field there
            if (!m_board.hasPiece(move.to())) {
              if (m_board.hasPiece(
                      Position(move.to().row() + 1, move.to().col()))) {
                Piece p = m_board.getPiece(
                    Position(move.to().row() + 1, move.to().col()));
                if (p.type() == PieceType::PAWN &&
                    p.color() == PlayerColor::WHITE) {
                  // this was an en-passant move, remove it
                  return false;
                }
              }
            }
          }
        }
      }
    }

    return true; // for now.
  } else {
    return false;
  }
}

void GameState::getEnPassantInformation(int &whiteEnPassant,
                                        int &blackEnPassant) const {
  whiteEnPassant = m_whiteEnPassant;
  blackEnPassant = m_blackEnPassant;
}

void GameState::applyMove(const Move &move) {

  if (!isValid(move)) {
    throw std::runtime_error("This move is not valid.");
  }

  // check if this is an castling move
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

  // if the goal location has an opponent piece, set this to capture it.
  if (m_board.hasPiece(move.to())) {
    Piece p = m_board.getPiece(move.to());
    if (m_nextPlayer == PlayerColor::WHITE) {
      m_capturedPiecesWhite.push_back(Piece(PlayerColor::BLACK, p.type()));
    } else {
      m_capturedPiecesBlack.push_back(Piece(PlayerColor::WHITE, p.type()));
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

  // TODO: update half-moves count.
  // castling does increase it
  // destroying castling right also increases it
  // pawn movement or capturing resets it.

  // if it is a en-passant killer move, remove the pawn
  if (m_nextPlayer == PlayerColor::WHITE) {
    if (move.piece() == PieceType::PAWN && move.from().row() == 4) {
      if (m_blackEnPassant == move.to().col() &&
          move.to() == Position(5, m_blackEnPassant)) {
        m_board.removePiece(Position(4, m_blackEnPassant));
        m_capturedPiecesWhite.push_back(
            Piece(PieceType::PAWN, PlayerColor::BLACK));
      }
    }
  } else {
    if (move.piece() == PieceType::PAWN && move.from().row() == 3) {
      if (m_whiteEnPassant == move.to().col() &&
          move.to() == Position(2, m_whiteEnPassant)) {
        m_board.removePiece(Position(3, m_whiteEnPassant));
        m_capturedPiecesBlack.push_back(
            Piece(PieceType::PAWN, PlayerColor::WHITE));
      }
    }
  }

  // reset en-passant
  if (m_nextPlayer == PlayerColor::BLACK && m_whiteEnPassant != -1)
    m_whiteEnPassant = -1;
  if (m_nextPlayer == PlayerColor::WHITE && m_blackEnPassant != -1)
    m_blackEnPassant = -1;

  // En-Passant: set corresponding column
  if (move.piece() == PieceType::PAWN) {
    if (std::abs(move.from().row() - move.to().row()) == 2) {
      // two steps are only valid if en-passant
      if (m_nextPlayer == PlayerColor::WHITE)
        m_whiteEnPassant = move.to().col();
      if (m_nextPlayer == PlayerColor::BLACK)
        m_blackEnPassant = move.to().col();
    }
  }

  // if a pawn reached the opposite border, perform a promotion
  if (move.piece() == PieceType::PAWN) {
    if (move.player() == PlayerColor::WHITE && move.to().row() == 7) {
      m_board.removePiece(move.to());
      m_board.placePiece(move.to(),
                         Piece(m_whitePromotionType, PlayerColor::WHITE));
    } else if (move.player() == PlayerColor::BLACK && move.to().row() == 0) {
      m_board.removePiece(move.to());
      m_board.placePiece(move.to(),
                         Piece(m_blackPromotionType, PlayerColor::BLACK));
    }
  }

  // TODO:
  // check if the other player is in check now and has no possibility to resolve
  // this.
  // --> checkmate

  // switch next player
  m_nextPlayer = (m_nextPlayer == PlayerColor::WHITE) ? PlayerColor::BLACK
                                                      : PlayerColor::WHITE;

  // increase full moves
  if (m_nextPlayer == PlayerColor::WHITE) {
    m_fullMoves++;
  }
}

std::vector<std::vector<bool>>
GameState::getValidMoves(const Position &position) const {

  std::vector<std::vector<bool>> ret;
  std::vector<bool> empty;
  empty.resize(8, false);
  ret.resize(8, empty);

  if (!m_board.hasPiece(position)) {
    throw std::runtime_error("There is no piece in this position.");
  }

  Piece p = m_board.getPiece(position);

  for (int i = 7; i > -1; i--) {
    for (int j = 0; j < 8; j++) {
      ret[i][j] = isValid(Move(p.color(), p.type(), position, Position(i, j)));
    }
  }

  return ret;
}

void GameState::getCapturedPieces(std::vector<Piece> &whiteCaptured,
                                  std::vector<Piece> &blackCaptured) const {
  whiteCaptured.reserve(m_capturedPiecesWhite.size());
  blackCaptured.reserve(m_capturedPiecesBlack.size());

  for (auto p : m_capturedPiecesWhite) {
    whiteCaptured.push_back(p);
  }
  for (auto p : m_capturedPiecesBlack) {
    blackCaptured.push_back(p);
  }
}

void GameState::setWhitePromotionType(PieceType type) {
  if (type == PieceType::PAWN || type == PieceType::KING) {
    throw std::runtime_error("This Promotion is not valid.");
  }
  m_whitePromotionType = type;
}

void GameState::setBlackPromotionType(PieceType type) {
  if (type == PieceType::PAWN || type == PieceType::KING) {
    throw std::runtime_error("This Promotion is not valid.");
  }
  m_blackPromotionType = type;
}