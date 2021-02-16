#include <chessEngine/version.h>
#include <iostream>

using namespace chessEngine;
int main(int argc, char const *argv[]) {
  std::cout << Version::changelog() << std::endl;

  return 0;
}
