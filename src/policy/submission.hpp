#pragma once
#include "../state/state.hpp"

class Submission{
public:
  static int judge(State *state, int depth, int alpha, int beta, bool player);
  static Move get_move(State *state, int depth);
  static int capture(State *state, Move i);
};