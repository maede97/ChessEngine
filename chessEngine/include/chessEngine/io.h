#pragma once

#include <chessEngine/state.h>
#include <string>

namespace chessEngine {

/**
 * @brief This class contains various helpers to read/write chess boards.
 */
class IO {
public:
  /**
   * @brief Create a gamestate from the Forsyth-Edwards representation.
   *
   * See https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
   * @param string The string to create the board from.
   * @todo This is only partly implemented. The board is read correctly, but the
   * other information is still neglected.
   */
  static GameState fromForsythEdwards(const char *festring);

  /**
   * @brief Create a Forsyth-Edwards string from a given gamestate.
   * @param state The state to create the string from.
   * @todo This is not implemented yet.
   */
  static std::string toForsythEdwards(const GameState &state);

  /**
   * @brief Write a simpler board representation to a string.
   * @attention This eliminates the colors, it is therefore not possible to see
   * which pieces belong to wich player!
   * @param board The board to write.
   */
  static std::string writeBoardToString(const Board &board);

  /**
   * @brief Write the white pieces of the board to a string.
   * @attention This only writes the white pieces, replacing the black pieces by
   * a space.
   * @param board The board to write.
   */
  static std::string writeWhitePiecesToString(const Board &board);

  /**
   * @brief Write the black pieces of the board to a string.
   * @attention This only writes the black pieces, replacing the white pieces by
   * a space.
   * @param board The board to write.
   */
  static std::string writeBlackPiecesToString(const Board &board);

  /**
   * @brief Write a board to the console.
   * @param board The board to write.
   * @param invertColors If you are in a terminal with dark background, you
   * might want to invert the colors by setting this flag to true.
   */
  static void writeBoardToConsole(const Board &board,
                                  bool invertColors = false);

  /**
   * @brief Returns the corresponding chess character (unicode, therefore 4
   * chars) for the given piece.
   * @param color The color of the piece.
   * @param type The type of the piece.
   * @attention The returned char array might not be in your character set. Use
   * pieceToCharSimple for an ASCII-representation.
   */
  static const char *pieceToChar(const PlayerColor &color,
                                 const PieceType &type);

  /**
   * @brief Returns the corresponding chess character (unicode, therefore 4
   * chars) for the given piece.
   * @param piece The piece.
   * @attention The returned char array might not be in your character set. Use
   * pieceToCharSimple for an ASCII-representation.
   */
  static const char *pieceToChar(const Piece &piece);

  /**
   * @brief Returns the corresponding chess character (ascii, 2 chars) for the
   * given piece.
   * @param color The color of the piece.
   * @param type The type of the piece.
   */
  static const char *pieceToCharSimple(const PlayerColor &color,
                                       const PieceType &type);
  /**
   * @brief Returns the corresponding chess character (ascii, 2 chars) for the
   * given piece.
   * @param piece The piece.
   */
  static const char *pieceToCharSimple(const Piece &piece);
};

} // namespace chessEngine