#include <chessEngine/board.h>
#include <chessEngine/io.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    Board b = Board::defaultBoard();

    //IO::writeBoardToConsole(b, true);
    std::cout << IO::writeWhitePiecesToString(b) << std::endl;
    std::cout << IO::writeBlackPiecesToString(b) << std::endl;

    std::cout << IO::writeBoardToString(b) << std::endl;

    return 0;
}
