#pragma once

#include <chessEngine/board.h>
#include <string>

namespace chessEngine {

/**
 * @brief This class contains various helpers to read/write chess boards.
 */
class IO {
public:
  /**
   * @brief Create a board from the Forsyth-Edwards representation.
   *
   * See https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
   * @param string The string to create the board from.
   * @todo This is not implemented yet.
   */
  static Board fromForsythEdwards(const char *string);

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
};

} // namespace chessEngine