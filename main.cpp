#include <iostream>
#include <chessEngine/version.h>

using namespace chessEngine;
int main(int argc, char const *argv[])
{
    std::cout << Version::changelog() << std::endl;

    return 0;
}
