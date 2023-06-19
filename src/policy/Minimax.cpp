#include <cstdlib>
#include <climits>

#include "../state/state.hpp"
#include "./Minimax.hpp"


int Minimax::judge(State *state, int depth, bool player){
  if(state->game_state == WIN) return player? INT_MAX : INT_MIN;
  if(depth == 0) return state->evaluate();
  if(player){
    state->score = INT_MIN;
    for(auto i : state->legal_actions){
        int result = judge(state->next_state(i), depth-1, false);
        state->score = (result > state->score)? result : state->score;
    }
  }
  else{
    state->score = INT_MAX;
    for(auto i : state->legal_actions){
        int result = judge(state->next_state(i), depth-1, true);
        state->score = (result < state->score)? result : state->score;
    }
  }
  return state->score;
}

Move Minimax::get_move(State *state, int depth){
    if(!state->legal_actions.size()) state->get_legal_actions();
    Move bestmove = state->legal_actions[0];
    int best = INT_MIN;
    for(auto i : state->legal_actions){
        int value = judge(state->next_state(i), depth, false);
        if(value > best){
            best = value;
            bestmove = i;
        }
    }
    return bestmove;
}