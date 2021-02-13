cmake_minimum_required(VERSION 3.8)

# ChessEngine
project(ChessEngineGui)

# Add source files
file(GLOB_RECURSE CXX_SOURCES src/*.cpp)

add_executable(ChessEngineGui ${CXX_SOURCES})

# Add all dependencies via external projects and ext
add_subdirectory(ext/glad)

FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/archive/3.3.2.zip
    URL_HASH MD5=69d0aa90a9278c0dd8be975d1ae4aaf2
    UPDATE_COMMAND "" CONFIGURE_COMMAND "" BUILD_COMMAND "" INSTALL_COMMAND ""
)
fetch(glfw)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG 7b53551032f5fdd7371afe4ca7e4fb607a12ea34
)
fetch(imgui)

# build options
set(GLFW_BUILD_EXAMPLES
    OFF
    CACHE BOOL "GLFW lib only"
)
set(GLFW_BUILD_TESTS
    OFF
    CACHE BOOL "GLFW lib only"
)
set(GLFW_BUILD_DOCS
    OFF
    CACHE BOOL "GLFW lib only"
)
set(GLFW_INSTALL
    OFF
    CACHE BOOL "GLFW lib only"
)

add_subdirectory(${glfw_SOURCE_DIR} glfw)

file(GLOB IMGUI_SOURCES ${imgui_SOURCE_DIR}/*.cpp)

# Tell ImGui to use GLAD
target_compile_definitions(ChessEngineGui PUBLIC -DIMGUI_IMPL_OPENGL_LOADER_GLAD)

target_sources(ChessEngineGui PUBLIC ${IMGUI_SOURCES} ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)

add_dependencies(ChessEngineGui glfw)
target_include_directories(ChessEngineGui PUBLIC include ext/glfw glad ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends chessEngine)
target_link_libraries(ChessEngineGui chessEngineLib glfw glad sqlite3)
