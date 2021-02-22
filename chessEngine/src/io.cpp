#include <chessEngine/io.h>
#include <iostream>
#include <string>

using namespace chessEngine;

GameState IO::fromForsythEdwards(const char *feString) {
  Board board = Board::emptyBoard();
  GameState ret;

  std::string string = std::string(feString);

  int pos = 0;
  for (int i = 7; i > -1; i--) {
    int column = 0;
    // read until we have a /, but at most 8 steps
    while (true) // column is increased below
    {
      if (string.at(pos) == '/') {
        // we found a /, move to next row
        pos++;
        break;
      } else if (column == 8) {
        pos++;
        break;
      } else {
        // read number or character
        if (std::isdigit(string.at(pos))) {
          column +=
              string.at(pos) - '0'; // convert to ascii code and subtract 0
          pos++;
        } else {
          // place a piece
          switch (string.at(pos)) {
          case 'p':
            board.placePiece(Position(i, column),
                             Piece(PieceType::PAWN, PlayerColor::BLACK));
            break;
          case 'n':
            board.placePiece(Position(i, column),
                             Piece(PieceType::KNIGHT, PlayerColor::BLACK));
            break;
          case 'b':
            board.placePiece(Position(i, column),
                             Piece(PieceType::BISHOP, PlayerColor::BLACK));
            break;
          case 'r':
            board.placePiece(Position(i, column),
                             Piece(PieceType::ROOK, PlayerColor::BLACK));
            break;
          case 'q':
            board.placePiece(Position(i, column),
                             Piece(PieceType::QUEEN, PlayerColor::BLACK));
            break;
          case 'k':
            board.placePiece(Position(i, column),
                             Piece(PieceType::KING, PlayerColor::BLACK));
            break;
          case 'P':
            board.placePiece(Position(i, column),
                             Piece(PieceType::PAWN, PlayerColor::WHITE));
            break;
          case 'N':
            board.placePiece(Position(i, column),
                             Piece(PieceType::KNIGHT, PlayerColor::WHITE));
            break;
          case 'B':
            board.placePiece(Position(i, column),
                             Piece(PieceType::BISHOP, PlayerColor::WHITE));
            break;
          case 'R':
            board.placePiece(Position(i, column),
                             Piece(PieceType::ROOK, PlayerColor::WHITE));
            break;
          case 'Q':
            board.placePiece(Position(i, column),
                             Piece(PieceType::QUEEN, PlayerColor::WHITE));
            break;
          case 'K':
            board.placePiece(Position(i, column),
                             Piece(PieceType::KING, PlayerColor::WHITE));
            break;
          default:
            throw std::runtime_error("Unknown character found.");
            break;
          }
          // move a column to the right
          column++;
          pos++;
        }
      }
    }
  }

  // read further information about the game

  ret.setBoard(board);
  return ret;
}

std::string IO::toForsythEdwards(const GameState &state) {
  std::string ret;

  // TODO

  return ret;
}

std::string IO::writeBoardToString(const Board &board) {
  std::string ret;
  // start at row = 8 and iterate down
  for (int r = 7; r > -1; r--) {
    for (int c = 0; c < 8; c++) {
      Board::map_t::const_iterator piece = board.m_board.find(Position(r, c));
      if (piece == board.m_board.cend()) {
        // no piece was found at this position, so print a space
        ret += " ";
      } else {
        switch (piece->second.type()) {
        case PieceType::PAWN:
          ret += "P";
          break;
        case PieceType::KNIGHT:
          ret += "N";
          break;
        case PieceType::BISHOP:
          ret += "B";
          break;
        case PieceType::ROOK:
          ret += "R";
          break;
        case PieceType::QUEEN:
          ret += "Q";
          break;
        case PieceType::KING:
          ret += "K";
          break;
        default:
          ret += "?";
        }
      }
    }
    ret += "\n";
  }

  return ret.substr(0, ret.length() - 1); // remove the last new line
}

std::string IO::writeWhitePiecesToString(const Board &board) {
  std::string ret;
  // start at row = 8 and iterate down
  for (int r = 7; r > -1; r--) {
    for (int c = 0; c < 8; c++) {
      Board::map_t::const_iterator piece = board.m_board.find(Position(r, c));
      if (piece == board.m_board.cend()) {
        // no piece was found at this position, so print a space
        ret += " ";
      } else {
        if (piece->second.color() == PlayerColor::WHITE) {
          switch (piece->second.type()) {
          case PieceType::PAWN:
            ret += "P";
            break;
          case PieceType::KNIGHT:
            ret += "N";
            break;
          case PieceType::BISHOP:
            ret += "B";
            break;
          case PieceType::ROOK:
            ret += "R";
            break;
          case PieceType::QUEEN:
            ret += "Q";
            break;
          case PieceType::KING:
            ret += "K";
            break;
          default:
            ret += "?";
          }
        } else {
          ret += " "; // white piece, add empty
        }
      }
    }
    ret += "\n";
  }

  return ret.substr(0, ret.length() - 1); // remove the last new line
}

std::string IO::writeBlackPiecesToString(const Board &board) {
  std::string ret;
  // start at row = 8 and iterate down
  for (int r = 7; r > -1; r--) {
    for (int c = 0; c < 8; c++) {
      Board::map_t::const_iterator piece = board.m_board.find(Position(r, c));
      if (piece == board.m_board.cend()) {
        // no piece was found at this position, so print a space
        ret += " ";
      } else {
        if (piece->second.color() == PlayerColor::BLACK) {
          switch (piece->second.type()) {
          case PieceType::PAWN:
            ret += "P";
            break;
          case PieceType::KNIGHT:
            ret += "N";
            break;
          case PieceType::BISHOP:
            ret += "B";
            break;
          case PieceType::ROOK:
            ret += "R";
            break;
          case PieceType::QUEEN:
            ret += "Q";
            break;
          case PieceType::KING:
            ret += "K";
            break;
          default:
            ret += "?";
          }
        } else {
          ret += " "; // white piece, add empty
        }
      }
    }
    ret += "\n";
  }
  return ret.substr(0, ret.length() - 1); // remove the last new line
}

void IO::writeBoardToConsole(const Board &board, bool invertColors) {
  // start at row = 8 and iterate down
  for (int r = 7; r > -1; r--) {
    std::cout << r << " "; // initial row
    for (int c = 0; c < 8; c++) {
      Board::map_t::const_iterator piece = board.m_board.find(Position(r, c));
      if (piece == board.m_board.cend()) {
        // no piece was found at this position, so print a space
        std::cout << " ";
      } else {
        // a piece was found, print it
        if ((piece->second.color() == PlayerColor::WHITE && !invertColors) ||
            (piece->second.color() == PlayerColor::BLACK && invertColors)) {
          std::cout << pieceToChar(
              Piece(PlayerColor::WHITE, piece->second.type()));
        } else {
          std::cout << pieceToChar(
              Piece(PlayerColor::BLACK, piece->second.type()));
        }
      }
    }
    std::cout << std::endl;
  }
  std::cout << "  01234567" << std::endl;
}

const char *IO::pieceToChar(const Piece &piece) {
  return pieceToChar(piece.color(), piece.type());
}

const char *IO::pieceToCharSimple(const Piece &piece) {
  return pieceToCharSimple(piece.color(), piece.type());
}

const char *IO::pieceToChar(const PlayerColor &color, const PieceType &type) {
  if (color == PlayerColor::WHITE) {
    switch (type) {
    case PieceType::PAWN:
      return "\u2659";
      break;
    case PieceType::KNIGHT:
      return "\u2658";
      break;
    case PieceType::BISHOP:
      return "\u2657";
      break;
    case PieceType::ROOK:
      return "\u2656";
      break;
    case PieceType::QUEEN:
      return "\u2655";
      break;
    case PieceType::KING:
      return "\u2654";
      break;
    default:
      return "?";
    }
  } else {
    switch (type) {
    case PieceType::PAWN:
      return "\u265F";
      break;
    case PieceType::KNIGHT:
      return "\u265E";
      break;
    case PieceType::BISHOP:
      return "\u265D";
      break;
    case PieceType::ROOK:
      return "\u265C";
      break;
    case PieceType::QUEEN:
      return "\u265B";
      break;
    case PieceType::KING:
      return "\u265A";
      break;
    default:
      return "?";
    }
  }
}

const char *IO::pieceToCharSimple(const PlayerColor &color,
                                  const PieceType &type) {
  if (color == PlayerColor::WHITE) {
    switch (type) {
    case PieceType::PAWN:
      return "WP";
      break;
    case PieceType::KNIGHT:
      return "WN";
      break;
    case PieceType::BISHOP:
      return "WB";
      break;
    case PieceType::ROOK:
      return "WR";
      break;
    case PieceType::QUEEN:
      return "WQ";
      break;
    case PieceType::KING:
      return "WK";
      break;
    default:
      return "?";
    }
  } else {
    switch (type) {
    case PieceType::PAWN:
      return "BP";
      break;
    case PieceType::KNIGHT:
      return "BN";
      break;
    case PieceType::BISHOP:
      return "BB";
      break;
    case PieceType::ROOK:
      return "BR";
      break;
    case PieceType::QUEEN:
      return "BQ";
      break;
    case PieceType::KING:
      return "BK";
      break;
    default:
      return "?";
    }
  }
}