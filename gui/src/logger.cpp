#include <ChessEngineGui/logger.h>

CHESS_NAMESPACE_BEGIN

std::vector<std::pair<ImVec4, std::string>> Logger::entries;

void Logger::logInfo(std::string what) {
  entries.push_back(std::make_pair(ImVec4(0, 1, 0, 1), what));
}

void Logger::logWarning(std::string what) {
  entries.push_back(std::make_pair(ImVec4(1, 0.6, 0, 1), what));
}

void Logger::displayConsole(int max) {
  int min_, max_;
  if (max == -1) {
    // display all
    min_ = 0;
    max_ = entries.size();
  } else {
    // display only last
    max_ = entries.size();
    min_ = std::max(0, max_ - max);
  }

  for (int i = min_; i < max_; i++) {
    ImGui::TextColored(entries[i].first, entries[i].second.c_str());
  }
}

CHESS_NAMESPACE_END