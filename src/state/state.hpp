#ifndef __STATE_H__
#define __STATE_H__

#include <string>
#include <cstdlib>
#include <vector>
#include <utility>
#include <map>

#include "../config.hpp"


typedef std::pair<size_t, size_t> Point;
typedef std::pair<Point, Point> Move;
class Board{
  public:
    char board[2][BOARD_H][BOARD_W] = {{
      //white
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1},
      {2, 3, 4, 5, 6},
    }, {
      //black
      {6, 5, 4, 3, 2},
      {1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
    }};

    char posValue[6][BOARD_H][BOARD_W] = {
      // 1: Pawn
      {
        {0,   0,   0,   0,   0},
        {50, 50,  50,  50,  50},
        {10, 20,  30,  20,  10},
        { 5, -5, -10,   0,   0},
        { 5, 10,  10, -20, -20},
        { 0,  0,   0,   0,   0}
      }, 
      // 2: Root
      {
        { 0,   0,   0,   0,   0},
        { 5,  10,  10,  10,   5},
        {-5,   0,   0,   0,  -5},
        {-5,   0,   0,   0,  -5},
        {-5,   0,   0,   0,  -5},
        { 0,   0,   5,   0,   0}
      },
      // 3: Knight
      {
        {-50, -40, -30, -40, -50},
        {-40, -20,   5, -20,  -5},
        {-30,   5,  15,   5, -30},
        {-30,   5,  15,   5, -30},
        {-40, -20,   5, -20,  -5},
        {-50, -40, -30, -40, -50}
      },
      // 4 : Bishop
      {
        {-20, -10, -10, -10, -20},
        {-10,   0,   0,   0, -10},
        {-10,   5,  10,   5, -10},
        {-10,  10,  10,  10, -10},
        {-10,   5,   0,   5, -10},
        {-20, -10, -10, -10, -20}
      },
      // 5 : Queen
      {
        {-20, -10,  -5, -10, -20},
        {-10,   0,   0,   0, -10},
        {-10,   5,   5,   5, -10},
        {-10,   5,   5,   5, -10},
        {-10,   0,   0,   0, -10},
        {-20, -10,  -5, -10, -20}
      },
      // 6 : King
      {
        {-30, -40, -50, -40, -30},
        {-30, -40, -50, -40, -30},
        {-30, -40, -50, -40, -30},
        {-10, -20, -20, -20, -10},
        { 20,  20,   0,  20,  20},
        { 20,  30,   0,  30,  20}
      },
    };
};

enum GameState {
  UNKNOWN = 0,
  WIN,
  DRAW,
  NONE
};


class State{
  public:
    //You may want to add more property for a state
    GameState game_state = UNKNOWN;
    Board board;
    int player = 0;
    int score = 0;
    bool promotion = false;
    std::vector<Move> legal_actions;
    std::map<Move, std::pair<int, int>> oppn;
    
    State(){};
    State(int player): player(player){};
    State(Board board): board(board){};
    State(Board board, int player): board(board), player(player){};
    
    int evaluate();
    State* next_state(Move move);
    void get_legal_actions();
    std::string encode_output();
    std::string encode_state();
};

#endif