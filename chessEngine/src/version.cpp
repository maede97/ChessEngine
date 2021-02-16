#include <chessEngine/version.h>

using namespace chessEngine;

double Version::version() { return 1.0; }

const char *Version::changelog() {
  return "ChessEngine\n"
         "Created by Matthias Busenhart.\n\n"
         "Changelog:\n"
         "Version 1.0\n"
         "===========\n"
         "- Internal Representation\n";
}