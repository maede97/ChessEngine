#pragma once

namespace chessEngine {
/**
 * @brief Class which holds information about the current Version of this
 * engine.
 */
class Version {
public:
  /**
   * @brief Returns the current version of this engine.
   */
  static double version();

  /**
   * @brief Returns the changelog of this engine.
   */
  static const char *changelog();
};

} // namespace chessEngine