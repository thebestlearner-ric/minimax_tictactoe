#include "../include/Game.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <tuple>
#include <vector>

#include "../include/Constants.h"
#include "Move.h"
#include "Player.h"

bool Game::game_over() {
  playerType winner = board_.CheckVictory();
  switch (winner) {
    case playerType::HUMAN_PLAYER:
      std::cout << "Human player won\n";
      minmax_ai_.SetAIinfo(ZEROS, LOSES);
      SetPlayerWins(WINS, ZEROS);
      return true;
    case playerType::AI_PLAYER:
      std::cout << "AI won\n";
      minmax_ai_.SetAIinfo(WINS, ZEROS);
      SetPlayerWins(ZEROS, LOSES);
      return true;
    case playerType::NO_WINNER:
      std::cout << "Draw\n";
      minmax_ai_.SetAIinfo(ZEROS, ZEROS);
      SetPlayerWins(ZEROS, ZEROS);
      return true;
    case playerType::IN_PLAY:
      std::cout << "IN PLAY\n";
      return false;
  }
  return false;
}

void Game::SetPlayerWins(int wins, int loses) {
  player_info_.num_of_wins += wins;
  player_info_.num_of_loss += loses;
}

void Game::CreatePlayer() {
  player_info_.player = playerType::HUMAN_PLAYER;
  player_info_.num_of_wins = 0;
  player_info_.num_of_loss = 0;
  player_info_.move.location = 0;
  player_info_.move.score = 0;
  player_info_.move.piece = X_VAL;
}

playerInfo Game::GetPlayerInfo() { return player_info_; }

void Game::PrintScoreBoard() {
  playerType info = GetPlayerInfo().player;
  if (info == playerType::HUMAN_PLAYER) {
    std::cout << "Human Player" << std::endl;
  }
  std::cout << "Number of Wins: " << GetPlayerInfo().num_of_wins << std::endl;
  std::cout << "Number of Loss: " << GetPlayerInfo().num_of_loss << std::endl;
  std::cout << "=======================\n";
  info = minmax_ai_.GetAIinfo()->player;
  if (info == playerType::AI_PLAYER) {
    std::cout << "AI Player" << std::endl;
  }
  std::cout << "Number of Wins: " << minmax_ai_.GetAIinfo()->num_of_wins
            << std::endl;
  std::cout << "Number of Loss: " << minmax_ai_.GetAIinfo()->num_of_loss
            << std::endl;
}

void Game::PrintGetPlayerMove() {
  std::cout << "Player " << std::endl;
  std::cout << "Please enter a move (0 to " << (board_.GetBoard().size() - 1)
            << "): ";
  std::cin >> player_info_.move.location;
  board_.SetMove(player_info_.move, player_info_.player);
  board_.PrintBoard(true);
}

void Game::performAImove(Board& board) {
  std::cout << "AI move" << std::endl;
  Move test_move;
  test_move = minmax_ai_.PerformMove(board);
  board_.SetMove(test_move, minmax_ai_.GetAIinfo()->player);
}

void Game::run() {
  CreatePlayer();
  board_.PrintBoard(true);
  while (game_over() == false) {
    PrintGetPlayerMove();
    performAImove(board_);
  }
  board_.PrintBoard();
  PrintScoreBoard();
}