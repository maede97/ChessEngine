cmake_minimum_required(VERSION 3.8)

################################
# GTest
################################
project(googletest-git NONE)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
)

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

################################
# Tests
################################
# Add test cpp file

file(GLOB TEST_SOURCES TEST_*.cpp)

foreach(cur_test IN ITEMS ${TEST_SOURCES})
    # remove .cpp in filename
    get_filename_component(cur_test_short ${cur_test} NAME_WLE)

    add_executable(${cur_test_short} ${cur_test})
    target_link_libraries(${cur_test_short} gtest gtest_main chessEngineLib)
    target_include_directories(${cur_test_short} PUBLIC chessEngineLib)
    add_test(NAME ${cur_test_short} COMMAND ${cur_test_short})
endforeach()


