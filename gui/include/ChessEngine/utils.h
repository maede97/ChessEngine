#pragma once

#include <stdexcept>
#include <string>

#define CHESS_NAMESPACE_BEGIN namespace ChessEngine {
#define CHESS_NAMESPACE_END }

#define MAKE_ERROR(A)                                                          \
  throw std::runtime_error(std::string(__FILE__) + ":" +                       \
                           std::to_string(__LINE__) + " " + A)
