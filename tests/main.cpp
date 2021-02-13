#include <gtest/gtest.h>

/**
 * This binary will run all tests found.
 */

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}