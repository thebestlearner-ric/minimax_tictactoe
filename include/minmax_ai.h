#pragma once

#include "../include/Player.h"
#include "../include/Board.h"
#include "Move.h"

class MINMAX{
    private:
    playerInfo AI_;
    Move GetBestMove(Board& board, playerType player);
    void CreateAI(playerType player = playerType::AI_PLAYER, char piece = O_VAL);
    public:
    MINMAX();
    MINMAX(playerType player, char piece);
    ~MINMAX();
    void SetAIinfo(Move& move);
    void SetAIinfo(int wins, int loss);
    playerInfo* GetAIinfo();
    void ClearAIinfo();
    void CopyBoard(Board& board);
    Move PerformMove(Board& board);
};