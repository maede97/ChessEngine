#include <chessEngine/board.h>
#include <chessEngine/io.h>

int main(int argc, char const *argv[])
{
    Board b = Board::defaultBoard();

    IO::writeBoardToConsole(b, true);

    return 0;
}
