#pragma once
#include <cstddef>
#include <ostream>

#include "../include/Move.h"

enum class playerType { AI_PLAYER, HUMAN_PLAYER, NO_WINNER, IN_PLAY };

struct playerInfo {
  playerType player;
  Move move;
  int num_of_wins;
  int num_of_loss;
  friend std::ostream& operator<<(std::ostream& stream, playerType const& obj) {
    switch (obj) {
      case playerType::AI_PLAYER:
        return stream << "AI player\n";
      case playerType::HUMAN_PLAYER:
        return stream << "Human player\n";
      case playerType::IN_PLAY:
        break;
      case playerType::NO_WINNER:
        return stream << "Draw\n";
    }
    return stream;
  }
};