#include "model.hpp"
Model::Model() : peg_count(0), game_state(PLAYING)
{
    initialize_board();
    start_timer();
}
void Model::initialize_board()
{
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if ((i == 0 || i == 1 || i == 5 || i == 6) && (j == 0 || j == 1 || j == 5 || j == 6))
            {
                board[i][j] = INVALID; // Invalid positions
            }
            else
            {
                board[i][j] = PEG; // All other positions are pegs
            }
        }
    }
    board[3][3] = EMPTY; // Center position is empty
    peg_count = 32;      // Total number of pegs on the board
}
// moves
bool Model::is_on_board(int x, int y) const
{
    return (x >= 0 && x < 7 && y >= 0 && y < 7 && board[x][y] != INVALID);
}
int Model::get_board_val(int x, int y) const
{
    if (is_on_board(x, y) == false)
    {
        throw OutOfBoardException("Move outside the board");
    }
    return board[x][y];
}
bool Model::is_valid_move(int from_x, int from_y, int to_x, int to_y) const
{
    // Check if positions are within bounds
    if (!is_on_board(from_x, from_y) || !is_on_board(to_x, to_y))
    {
        return false;
    }

    // Check if source has a peg and destination is empty
    if (board[from_x][from_y] != PEG || board[to_x][to_y] != EMPTY)
    {
        return false;
    }

    // Check if the move is horizontal or vertical and exactly 2 squares
    if (abs(from_x - to_x) == 2 && from_y == to_y)
    {
        // Horizontal move - check middle piece
        int middle_x = (from_x + to_x) / 2;
        return (board[middle_x][from_y] == PEG);
    }
    else if (abs(from_y - to_y) == 2 && from_x == to_x)
    {
        // Vertical move - check middle piece
        int middle_y = (from_y + to_y) / 2;
        return (board[from_x][middle_y] == PEG);
    }

    return false; // Not a valid move format
}

void Model::make_move(int from_x, int from_y, int to_x, int to_y)
{
    if (!is_valid_move(from_x, from_y, to_x, to_y))
    {
        if (!is_on_board(from_x, from_y) || !is_on_board(to_x, to_y))
        {
            throw OutOfBoardException("Move outside the board");
        }
        if (board[from_x][from_y] != PEG)
        {
            throw EmptyFieldException("Cannot select an empty field");
        }
        if (board[to_x][to_y] != EMPTY)
        {
            throw OccupiedFieldException("Target field is already occupied");
        }
        if (abs(from_x - to_x) == 2 && from_y == to_y)
        {
            if (board[(from_x + to_x) / 2][from_y] != PEG)
            {
                throw NoMiddlePieceException("No piece to jump over");
            }
        }
        else if (abs(from_y - to_y) == 2 && from_x == to_x)
        {
            if (board[from_x][(from_y + to_y) / 2] != PEG)
            {
                throw NoMiddlePieceException("No piece to jump over");
            }
        }
        else
        {
            throw InvalidMoveFormatException("Invalid move format");
        }
    }

    board[from_x][from_y] = EMPTY;
    board[to_x][to_y] = PEG;
    board[(from_x + to_x) / 2][(from_y + to_y) / 2] = EMPTY;
    peg_count--;
    update_game_state();
}
bool Model::has_moves_available() const
{
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (board[i][j] == PEG)
            {
                // Check horizontal moves
                if ((is_on_board(i + 2, j) && board[i + 1][j] == PEG && board[i + 2][j] == EMPTY) ||
                    (is_on_board(i - 2, j) && board[i - 1][j] == PEG && board[i - 2][j] == EMPTY) ||
                    (is_on_board(i, j + 2) && board[i][j + 1] == PEG && board[i][j + 2] == EMPTY) ||
                    (is_on_board(i, j - 2) && board[i][j - 1] == PEG && board[i][j - 2] == EMPTY))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
void Model::reset_game()
{
    initialize_board();
    reset_timer();
    peg_count = 32;
    game_state = PLAYING;
}
// time
void Model::start_timer()
{
    start_time = time(nullptr);
}
void Model::reset_timer()
{
    start_time = time(nullptr);
}
double Model::get_game_time() const
{
    return difftime(time(nullptr), start_time);
}
// state
void Model::set_game_state(state game_state)
{
    this->game_state = game_state;
}
state Model::get_game_state() const
{
    return game_state;
}
int Model::get_peg_count() const
{
    return peg_count;
}
void Model::update_game_state()
{
    if (peg_count == 1)
    {
        game_state = WIN;
    }
    else if (!has_moves_available())
    {
        game_state = LOST;
    }
}
// ---