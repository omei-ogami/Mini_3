#include <cstdlib>

#include "../state/state.hpp"
#include "./Minimax.hpp"


int Minimax::judge(State *state, int depth, bool player){
  if(depth == 0 || state->game_state != UNKNOWN) return state->evaluate();
  if(player){
    state->score = -1000000;
    if(!state->legal_actions.size()) state->get_legal_actions();
    for(auto i : state->legal_actions){
        int result = judge(state->next_state(i), depth-1, false);
        state->score = (result > state->score)? result : state->score;
    }
  }
  else{
    state->score = 1000000;
    if(!state->legal_actions.size()) state->get_legal_actions();
    for(auto i : state->legal_actions){
        int result = judge(state->next_state(i), depth-1, true);
        state->score = (result < state->score)? result : state->score;
    }
  }
  return state->score;
}

Move Minimax::get_move(State *state, int depth){
    if(!state->legal_actions.size()) state->get_legal_actions();
    Move bestmove;
    int best = -1000000;
    for(auto i : state->legal_actions){
        int value = judge(state->next_state(i), depth, true);
        if(value > best){
            best = value;
            bestmove = i;
        }
    }
    return bestmove;
}