#pragma once

#include <chessEngine/move.h>
#include <chessEngine/piece.h>
#include <chessEngine/position.h>
#include <unordered_map>
#include <vector>

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

  /**
   * @brief Place a piece on the board.
   * @param position The position on which the piece should be placed.
   * @param piece The piece which should be placed.
   * @throws std::runtime_error If the position is already occupied.
   */
  void placePiece(const Position &position, const Piece &piece);

  /**
   * @brief Removes a piece from the board given a position.
   * @param position The position from where the piece should be removed.
   * @throws std::runtime_error If no piece is at that position.
   */
  void removePiece(const Position &position);

  /**
   * @brief Get the piece from a given position.
   * @param position The position of the piece.
   * @throws std::runtime_error If no piece is at that position.
   */
  Piece getPiece(const Position &position) const;

  /**
   * @brief Compare two boards piece by piece.
   * @param board The other board to compare to.
   * @return Whether the two boards are equal.
   */
  bool operator==(const Board &board) const;

  /**
   * @brief Compare two boards piece by piece.
   * @param board The other board to compare to.
   * @return Whether the two boards are not equal.
   */
  bool operator!=(const Board &board) const;

  /**
   * @brief Applies a move to the board.
   * @param move The move to apply.
   * @throws std::runtime_error If the piece is not at the start position of the
   * move.
   */
  void applyMove(const Move &move);

  /**
   * @brief Gets an 2D array of all valid moves of the given piece.
   * @param position The position of the piece to get the valid moves.
   * @throws std::runtime_error If no piece is in this position.
   * @attention This does not cover attack moves from pawns!
   */
  std::vector<std::vector<bool>> getValidMoves(const Position &position);

private:
  friend IO;     ///< all IO functions should have access to private members.
  map_t m_board; ///< Internal storage of the board state (using map_t).
};

} // namespace chessEngine

/**
 * @brief Print a board to a stream.
 * @param os The stream to write to.
 * @param board The board to print.
 */
std::ostream &operator<<(std::ostream &os, const chessEngine::Board &board);
