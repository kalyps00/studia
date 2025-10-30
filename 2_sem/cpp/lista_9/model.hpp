#ifndef MODEL_HPP
#define MODEL_HPP
#include <time.h>
#include "exceptions.hpp"
enum state
{
    PLAYING,
    RESTART,
    LOST,
    WIN,
    SURRENDER,
    QUIT
};

class Model
{
private:
    int peg_count;
    int board[7][7];
    state game_state;
    time_t start_time;
    static const int EMPTY = 0;
    static const int PEG = 1;
    static const int INVALID = -1;

public:
    Model();
    void initialize_board();
    // moves
    void make_move(int from_x, int from_y, int to_x, int to_y);
    bool is_valid_move(int from_x, int from_y, int to_x, int to_y) const;
    bool is_on_board(int x, int y) const;
    bool has_moves_available() const;

    // state
    void set_game_state(state game_state);
    state get_game_state() const;
    int get_peg_count() const;
    void reset_game();
    void update_game_state();

    // board
    int get_board_val(int x, int y) const;

    // time
    void start_timer();
    double get_game_time() const;
    void reset_timer();
};
#endif // MODEL_HPP