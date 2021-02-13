cmake_minimum_required(VERSION 3.8)

project(Chess)

include(FetchContent)
macro(fetch what)
    FetchContent_GetProperties("${what}")
    if(NOT ${${what}_POPULATED})
        message(STATUS "fetching ${what} ...")
        FetchContent_Populate(${what})
    endif()
    mark_as_advanced(${${what}_SOURCE_DIR})
endmacro()

option(BUILD_GUI "Build the GUI" OFF)
option(BUILD_TESTS "Build unit tests" ON)

add_subdirectory(chessEngine)

if(${BUILD_GUI})
    add_subdirectory(gui)
endif()

if(${BUILD_TESTS})
    add_subdirectory(tests)
endif()