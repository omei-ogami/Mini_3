#pragma once
#include "../state/state.hpp"

class Minimax{
public:
  static int judge(State *state, int depth, bool player);
  static Move get_move(State *state, int depth);
};