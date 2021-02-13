cmake_minimum_required(VERSION 3.8)

project(Chess)

add_subdirectory(chessEngine)
add_subdirectory(gui)

enable_testing()
add_subdirectory(tests)
