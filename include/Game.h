#pragma once
#include "../include/Constants.h"
#include "../include/Move.h"
#include "../include/Board.h"
#include "../include/minmax_ai.h"
#include "Player.h"
#include <vector>
#include <ostream>

class Game{
    private:
    Board board_;
    MINMAX minmax_ai_;
    playerInfo player_info_;
    bool game_over();
    playerInfo GetPlayerInfo();
    void SetPlayerWins(int wins, int loses);
    void CreatePlayer();
    void PrintScoreBoard();
    void PrintGetPlayerMove();
    void performAImove(Board& board);
    public:
    void run();
};