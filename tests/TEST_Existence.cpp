#include <chessEngine/version.h>
#include <gtest/gtest.h>
using namespace chessEngine;

/**
 * This file contains unit tests for random checks, whether the library is built
 * correctly or not
 */

TEST(Existence, TestVersion) {
  double v = Version::version();
  // Assume at least version 1.0
  EXPECT_TRUE(v >= 1.0);
}

TEST(Existence, Changelog) {
  const char *cl = Version::changelog();
  EXPECT_TRUE(sizeof(cl) > 0);
}