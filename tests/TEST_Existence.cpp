#include <chessEngine/version.h>
#include <gtest/gtest.h>

/**
 * This file contains unit tests for random checks, whether the library is built correctly or not
 */

TEST(Existence, TestVersion) {
    double version = getVersion();
    // Assume at least version 1.0
    EXPECT_TRUE(version >= 1.0);
}