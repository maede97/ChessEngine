cmake_minimum_required(VERSION 3.8)

project(ChessEngineTests)

enable_testing()

################################
# GTest
################################
# FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY https://github.com/google/googletest.git
#   GIT_TAG        release-1.8.0
# )
# fetch(googletest)

find_package(GTest REQUIRED)

################################
# Tests
################################
# Add test cpp files

file(GLOB TEST_SOURCES *.cpp)
add_executable(unittests ${TEST_SOURCES})
add_test(NAME unittests COMMAND unittests)
target_link_libraries(unittests chessEngineLib GTest::GTest GTest::Main)
target_include_directories(unittests PUBLIC chessEngineLib GTest::GTest)