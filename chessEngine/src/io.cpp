#include <chessEngine/io.h>
#include <iostream>

Board IO::fromForsythEdwards(const char *feString)
{
    Board board = Board::emptyBoard();

    // TODO

    return board;
}

void IO::writeBoardToConsole(const Board &board, bool invertColors)
{
    // start at row = 8 and iterate down
    for (int r = 7; r > -1; r--)
    {
        for (int c = 0; c < 8; c++)
        {
            Board::map_t::const_iterator piece = board.m_board.find(Position(r, c));
            if (piece == board.m_board.cend())
            {
                // no piece was found at this position, so print a space
                std::cout << " ";
            }
            else
            {
                // a piece was found, print it
                if ((piece->second.color() == PlayerColor::WHITE && !invertColors) || (piece->second.color() == PlayerColor::BLACK && invertColors))
                {
                    switch (piece->second.type())
                    {
                    case PieceType::PAWN:
                        std::cout << "\u2659";
                        break;
                    case PieceType::KNIGHT:
                        std::cout << "\u2658";
                        break;
                    case PieceType::BISHOP:
                        std::cout << "\u2657";
                        break;
                    case PieceType::ROOK:
                        std::cout << "\u2656";
                        break;
                    case PieceType::QUEEN:
                        std::cout << "\u2655";
                        break;
                    case PieceType::KING:
                        std::cout << "\u2654";
                        break;
                    default:
                        std::cout << "?";
                    }
                }
                else
                {
                    switch (piece->second.type())
                    {
                    case PieceType::PAWN:
                        std::cout << "\u265F";
                        break;
                    case PieceType::KNIGHT:
                        std::cout << "\u265E";
                        break;
                    case PieceType::BISHOP:
                        std::cout << "\u265D";
                        break;
                    case PieceType::ROOK:
                        std::cout << "\u265C";
                        break;
                    case PieceType::QUEEN:
                        std::cout << "\u265B";
                        break;
                    case PieceType::KING:
                        std::cout << "\u265A";
                        break;
                    default:
                        std::cout << "?";
                    }
                }
            }
        }
        std::cout << std::endl;
    }
}