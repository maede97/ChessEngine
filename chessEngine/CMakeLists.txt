cmake_minimum_required(VERSION 3.8)

project(chessEngineLib)

file(GLOB_RECURSE CXX_SOURCES src/*.cpp)

add_library(chessEngineLib STATIC ${CXX_SOURCES})

target_include_directories(chessEngineLib PUBLIC include)

# target_link_libraries