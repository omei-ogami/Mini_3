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
            result += capture(state, i);
            if(state->promotion) result += 800;
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
            result -= capture(state, i);
            if(state->promotion) result -= 800;
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

//         Attacker    0  1    2    3    4    5    6       Victim
int MVV_LVA[7][7] =  {{0, 0,   0,   0,   0,   0,   0},     //0
                      {0, 150, 120, 140, 130, 110, 100},   //1
                      {0, 450, 420, 440, 430, 410, 400},   //2
                      {0, 250, 220, 240, 230, 210, 200},   //3
                      {0, 350, 320, 340, 330, 310, 300},   //4
                      {0, 550, 520, 540, 530, 510, 500},   //5
                      {0, 0,   0,   0,   0,   0,   0}};    //6 (WIN)

int AlphaBeta::capture(State *state, Move i){
    int victim = state->oppn[i].first, attacker = state->oppn[i].second;
    return MVV_LVA[victim][attacker];
}