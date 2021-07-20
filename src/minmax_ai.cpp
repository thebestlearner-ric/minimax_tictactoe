#include "../include/minmax_ai.h"

#include <iostream>
#include <memory>
#include <vector>

#include "../include/Constants.h"
#include "../include/Player.h"
#include "Move.h"

MINMAX::MINMAX() { CreateAI(playerType::AI_PLAYER, O_VAL); }
MINMAX::MINMAX(playerType player, char piece) { CreateAI(player, piece); }
MINMAX::~MINMAX() { ClearAIinfo(); }

void MINMAX::CreateAI(playerType player, char piece) {
  this->AI_.num_of_loss = 0;
  this->AI_.num_of_wins = 0;
  this->AI_.move.score = 0;
  this->AI_.move.location = 0;
  this->AI_.move.piece = piece;
  this->AI_.player = player;
}

void MINMAX::SetAIinfo(int wins, int loss) {
  this->AI_.num_of_wins += wins;
  this->AI_.num_of_loss += loss;
}

void MINMAX::SetAIinfo(Move& move) { this->AI_.move = move; }

playerInfo* MINMAX::GetAIinfo() { return &AI_; }

void MINMAX::ClearAIinfo() {
  this->AI_.num_of_loss = 0;
  this->AI_.num_of_wins = 0;
  this->AI_.move.score = 0;
  this->AI_.move.location = 0;
  this->AI_.move.piece = O_VAL;
}

Move MINMAX::PerformMove(Board& board) {
  Board ai_board_;
  ai_board_ = board;
  Move move;
  move = GetBestMove(ai_board_, playerType::AI_PLAYER);
  return move;
}

Move MINMAX::GetBestMove(Board& board, playerType player) {
  // Terminating condition
  playerType victor = board.CheckVictory();
  switch (victor) {
    case playerType::AI_PLAYER:
    // std::cout << "MINMAX AI PLAYER\n";
      return Move(10);
    case playerType::HUMAN_PLAYER:
    // std::cout << "MINMAX HUMAN PLAYER\n";
      return Move(-10);
    case playerType::NO_WINNER:
    // std::cout << "MINMAX DRAW\n";
      return Move(0);
    case playerType::IN_PLAY:
    // std::cout << "MINMAX STILL PLAYING\n";
      break;
  }
  std::vector<Move> moves;
  // Recursion
  for (int i = 0; i < board.GetBoard().size(); i++) {
    if (board.GetBoard()[i] == NO_VAL) {
      Move temp_move;
      temp_move.score = 0;
      temp_move.location = i;
      temp_move.piece = O_VAL;
      if (board.SetMove(temp_move, player, false) == false){
        break;
        // return Move(0);
      }
      // std::cout << "MINMAX piece at i: " << board.GetBoard()[i] << std::endl;
      // std::cout << "MINMAX value of i: " << i << std::endl;
      if (player == playerType::AI_PLAYER) {
        temp_move.score = GetBestMove(board, playerType::HUMAN_PLAYER).score;
      } else {
        temp_move.score = GetBestMove(board, playerType::AI_PLAYER).score;
      }
      moves.push_back(temp_move);
      // std::cout << "MINMAX temp score: " << temp_move.score << std::endl;
      temp_move.piece = NO_VAL;
      if (board.SetMove(temp_move, player, true) == false) {
        break;
      }
    }
  }
  // pick best move for the current player
  int best_move = 0;
  if (player == playerType::AI_PLAYER) {
    int best_score = -100000;
    for (int i = 0; i < moves.size(); i++) {
      if (moves[i].score > best_score) {
        best_move = i;
        best_score = moves[i].score;
      }
    }
  } else {
    int best_score = 100000;
    for (int i = 0; i < moves.size(); i++) {
      if (moves[i].score < best_score) {
        best_move = i;
        best_score = moves[i].score;
      }
    }
  }
  return moves[best_move];
}
