#include <cstdlib>
#include <climits>
#include <map>
#include <algorithm>

#include "../state/state.hpp"
#include "./submission.hpp"

//Copy from AlphaBeta

int Submission::judge(State *state, int depth, int alpha, int beta, bool player){
    if(state->game_state == WIN) return player? INT_MAX : INT_MIN;
    if(depth == 0) return state->evaluate();
    if(player){
        int score = INT_MIN;
        for(auto i : state->legal_actions){
            int result = judge(state->next_state(i), depth-1, alpha, beta, false);
            score += capture(state, i);
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
            score -= capture(state, i);
            score = (score < result)? score : result;
            beta = (beta < score)? beta : score;
            if(beta <= alpha) break;
        }
        return score;
    }
}

Move Submission::get_move(State *state, int depth){
    if(!state->legal_actions.size()) state->get_legal_actions();
    Move bestmove = state->legal_actions[0];
    int best = INT_MIN;
    for(auto i : state->legal_actions){
        int value = judge(state->next_state(i), depth, INT_MIN, INT_MAX, false);
        if(value > best){
            best = value;
            bestmove = i;
        }
    }
    return bestmove;
}

//         Attacker    0  1   2   3   4   5   6      Victim
int sub_MVV_LVA[7][7] =  {{0, 0,  0,  0,  0,  0,  0},    //0
                      {0, 15, 12, 14, 13, 11, 10},   //1
                      {0, 45, 42, 44, 43, 41, 40},   //2
                      {0, 25, 22, 24, 23, 21, 20},   //3
                      {0, 35, 32, 34, 33, 31, 30},   //4
                      {0, 55, 52, 54, 53, 51, 50},   //5
                      {0, 0,  0,  0,  0,  0,  0}};   //6 (WIN)

int Submission::capture(State *state, Move i){
    int victim = state->oppn[i].first, attacker = state->oppn[i].second;
    return sub_MVV_LVA[victim][attacker];
}