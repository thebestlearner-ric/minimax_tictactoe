#include "../include/Board.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "Player.h"

Board::Board() {
  game_grid_.fill('_');
  // PrintBoard(true);
  // std::cout << "Board Created" << std::endl;
}
Board::Board(const Board& var_board) {
  game_grid_ = var_board.game_grid_;
  board_length_ = var_board.board_length_;
}
Board::~Board() { Board::ClearBoard(); }
void Board::ClearBoard() { game_grid_.fill('_'); }
inline int Board::GetBoardSize() { return board_length_; }

void Board::PrintBoard(bool printIndex) {
  // print cell numbers and board values side by side
  int index = 0;
  for (auto& element : game_grid_) {
    // board grid
    if (printIndex == true) {
      std::cout << index << ":\t"
                << " | " << element << " | ";
    } else {
      std::cout << " | " << element << " | ";
    }
    // board index
    index++;
    if (index % GetBoardSize() == 0) {
      std::cout << '\n';
    }
  }
  std::cout << std::endl;
}

char Board::GetBoard(Move& move) { return game_grid_.at(move.location); }
std::array<char, DIMENSION * DIMENSION> Board::GetBoard() { return game_grid_; }

bool Board::SetMove(Move& move, playerType& player, bool isUndo) {
  // if (player == playerType::HUMAN_PLAYER) {
  //   move.piece = 'X';
  // }
  // std::cout << "board move location\n" << move.location << std::endl;
  if (move.location > GetBoard().size()) {
    // std::cout << "board Out of Bound\n";
    return false;
  } else if (GetBoard(move) != '_' && isUndo == false) {
    // std::cout << "board ilegal move\n";
    return false;
  } else if (GetBoard(move) == '_' || isUndo == true) {
    game_grid_[move.location] = move.piece;
    if (player == playerType::AI_PLAYER) {
      // std::cout << "board AI Move made\n";
    } else if (player == playerType::HUMAN_PLAYER) {
      // std::cout << "board Human Move made\n";
    }
    return true;
  } else {
    // std::cout << "board no move made\n";
    return false;
  }
}

char Board::CheckWinLeftDiagonal() {
  int number_of_O = 0, number_of_X = 0;
  int index = 0;
  for (int i = 0; i < game_grid_.size(); i = ((GetBoardSize() + 1) + i)) {
    switch (game_grid_[i]) {
      case 'O':
        ++number_of_O;
        break;
      case 'X':
        ++number_of_X;
        break;
    }
    if (number_of_O == GetBoardSize()) {
      return 'O';
    }
    if (number_of_X == GetBoardSize()) {
      return 'X';
    }
  }
  return '\0';
}

char Board::CheckWinRightDiagonal() {
  int number_of_O = 0, number_of_X = 0;
  int index = 0;
  for (int i = (GetBoardSize() - 1);
       i < (game_grid_.size() - (GetBoardSize() - 1));
       i = ((GetBoardSize() - 1) + i)) {
    switch (game_grid_[i]) {
      case 'O':
        ++number_of_O;
        break;
      case 'X':
        ++number_of_X;
        break;
    }
    if (number_of_O == GetBoardSize()) {
      return 'O';
    }
    if (number_of_X == GetBoardSize()) {
      return 'X';
    }
  }
  return '\0';
}

char Board::CheckWinColumn() {
  int number_of_O = 0, number_of_X = 0, index = 0;
  std::array<int, DIMENSION> column_X;
  std::array<int, DIMENSION> column_O;
  column_X.fill(0);
  column_O.fill(0);
  for (int i = 0; i < GetBoardSize(); i++) {
    for (int j = i; j < game_grid_.size(); j = (GetBoardSize() + j)) {
      ++index;
      switch (game_grid_[j]) {
        case 'O':
          ++number_of_O;
          break;
        case 'X':
          ++number_of_X;
          break;
      }
      column_O[i] = number_of_O;
      column_X[i] = number_of_X;
      if (index == GetBoardSize()) {
        index = 0;
        number_of_X = 0;
        number_of_O = 0;
      }
      if (column_O[i] == GetBoardSize()) {
        return 'O';
      } else if (column_X[i] == GetBoardSize()) {
        return 'X';
      }
    }
  }
  return '\0';
}

char Board::CheckWinRow() {
  int number_of_O = 0, number_of_X = 0, index = 0;
  for (int i = index; i < game_grid_.size(); i++) {
    if (i % GetBoardSize() == 0) {
      index = i;
      number_of_X = 0;
      number_of_O = 0;
    }
    switch (game_grid_[i]) {
      case 'O':
        ++number_of_O;
        break;
      case 'X':
        ++number_of_X;
        break;
    }
    if (index % GetBoardSize() == 0) {
      if (number_of_O == GetBoardSize()) {
        return 'O';
      }
      if (number_of_X == GetBoardSize()) {
        return 'X';
      }
    }
  }
  return '\0';
}

playerType Board::CheckVictory() {
  std::map<std::string, char> victory_map;
  playerType victor;
  // make iterator
  std::map<std::string, char>::iterator itr;
  victory_map.emplace(std::make_pair(ROW, CheckWinRow()));
  victory_map.emplace(std::make_pair(COL, CheckWinColumn()));
  victory_map.emplace(std::make_pair(LEFT, CheckWinLeftDiagonal()));
  victory_map.emplace(std::make_pair(RIGHT, CheckWinRightDiagonal()));
  for (auto& grid : GRIDS) {
    for (itr = victory_map.find(grid); itr != victory_map.end(); itr++) {
      if (itr->second == 'X') {
        // std::cout << "Win at " << itr->first << ' ' << itr->second << " Won"
                  // << std::endl;
        return playerType::HUMAN_PLAYER;
      } else if (itr->second == 'O') {
        // std::cout << "Win at " << itr->first << ' ' << itr->second << " Won"
                  // << std::endl;
        return playerType::AI_PLAYER;
      } else if (itr->second == '\0') {
        victor = playerType::IN_PLAY;
      } else {
        victor = playerType::NO_WINNER;
      }
    }
  }
  return victor;
}