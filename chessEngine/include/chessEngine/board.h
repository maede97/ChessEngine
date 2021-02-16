#pragma once

#include <chessEngine/piece.h>
#include <chessEngine/position.h>
#include <unordered_map>

namespace chessEngine {
// forward declaration of IO class for friend
class IO;

/**
 * @brief Helper to return the hash of a position.
 */
struct KeyHash {
  /**
   * @brief Returns the hash of a position.
   * @param k The position from which to generate the hash.
   * @return The hash calculated from Position::hash
   */
  std::size_t operator()(const Position &k) const { return k.hash(); }
};

/**
 * @brief Helper to check for two positions to be equal.
 */
struct KeyEqual {
  /**
   * @brief Compares two positions based on their hash (which is unique).
   * @param lhs The first position to compare.
   * @param rhs The second position to compare.
   * @return Whether the positions are the same based on their hash.
   */
  bool operator()(const Position &lhs, const Position &rhs) const {
    return lhs.hash() == rhs.hash();
  }
};

/**
 * @brief Class to store a chess board.
 */
class Board {
public:
  /**
   * @brief The type to use for storing the board inside a map.
   *
   * This map should have O(1) write and read.
   */
  using map_t = std::unordered_map<Position, Piece, KeyHash, KeyEqual>;

  /**
   * @brief Creates a default chess starting board.
   * @return The chess board created.
   */
  static Board defaultBoard();
  /**
   * @brief Creates an empty chess board.
   * @return The chess board created.
   */
  static Board emptyBoard();

  /**
   * @brief We do not allow a default constructor.
   */
  Board() = delete;

  /**
   * @brief Create a board from a given position map.
   * @param positions A map (using map_t) with all the chess pieces.
   */
  Board(map_t positions);

  /**
   * @brief Helper to get the number of pieces on this board.
   * @return The number of pieces.
   */
  size_t numPieces() const;

private:
  friend IO;     ///< all IO functions should have access to private members.
  map_t m_board; ///< Internal storage of the board state (using map_t).
};

} // namespace chessEngine