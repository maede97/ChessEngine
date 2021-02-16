#pragma once

#include "utils.h"
#include <imgui.h>
#include <vector>

CHESS_NAMESPACE_BEGIN

class Logger {
public:
  static void logInfo(std::string what);
  static void logWarning(std::string what);

  static void displayConsole(int max = -1);

private:
  static std::vector<std::pair<ImVec4, std::string>> entries;
};

CHESS_NAMESPACE_END