#pragma once
#include "../state/state.hpp"

class AlphaBeta{
public:
  static int judge(State *state, int depth, int alpha, int beta, bool player);
  static Move get_move(State *state, int depth);
};