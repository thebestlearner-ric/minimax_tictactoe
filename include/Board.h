#pragma once
#include <array>
#ifndef TICTACTOE_BOARD_H
#define TICTACTOE_BOARD_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../include/Constants.h"
#include "../include/Move.h"
#include "../include/Player.h"

class Board {
 private:
  std::array<char, DIMENSION * DIMENSION> game_grid_;
  int board_length_ = DIMENSION;
  char CheckWinLeftDiagonal();
  char CheckWinRightDiagonal();
  char CheckWinColumn();
  char CheckWinRow();
 public:
  Board();
  Board(const Board &var_board); 
  ~Board();
  int GetBoardSize();
  void ClearBoard();
  void SetAIGame();
  std::array<char, DIMENSION * DIMENSION> GetBoard();
  char GetBoard(Move &move);
  bool SetMove(Move& move, playerType& player, bool isUndo = false);
  void PrintBoard(bool printIndex = false);
  playerType CheckVictory();
};

#endif