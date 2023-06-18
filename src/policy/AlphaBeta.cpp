#include <cstdlib>
#include <climits>

#include "../state/state.hpp"
#include "./AlphaBeta.hpp"

int AlphaBeta::judge(State *state, int depth, int alpha, int beta, bool player){
    if(state->game_state == WIN) return player? INT_MIN : INT_MAX;
    if(depth == 0) return state->evaluate();
    if(player){
        int score = INT_MIN;
        for(auto i : state->legal_actions){
            int result = judge(state->next_state(i), depth-1, alpha, beta, false);
            score = (result > score)? result : score;
            alpha = (alpha > score)? alpha : score;
            if(beta <= alpha) break;
        }
        return score;
    }
    else{
        int score = INT_MAX;
        for(auto i : state->legal_actions){
            int result = judge(state->next_state(i), depth-1, alpha, beta, true);
            score = (score < result)? score : result;
            beta = (beta < score)? beta : score;
            if(beta <= alpha) break;
        }
        return score;
    }
}

Move AlphaBeta::get_move(State *state, int depth){
    if(!state->legal_actions.size()) state->get_legal_actions();
    Move bestmove = state->legal_actions[0];
    int best = INT_MIN;
    for(auto i : state->legal_actions){
        int value = judge(state->next_state(i), depth, INT_MIN, INT_MAX, true);
        if(value > best){
            best = value;
            bestmove = i;
        }
    }
    return bestmove;
}