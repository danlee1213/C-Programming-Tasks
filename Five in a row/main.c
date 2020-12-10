#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Basics.h"
#include "GameField.h"


int select_mode(){
  printf("Please select the mode\n");
  printf("1. Player VS Player\n");
  printf("2. Player VS Computer\n");
  SELECT_MODE choose_mode;
  while(choose_mode != 1 && choose_mode != 2){
      scanf("%d",&choose_mode);
    if(choose_mode != 1 && choose_mode != 2){
      printf("Check your input again!\n");
    }
    else{
      break;
    }
  }
  return choose_mode;
}


void player1_game(struct FiveInRowField *board){
  print_board(board->boardsize);
  printf("Player 1, it's your turn!\n");
  bool setXstatus = false;
  while(!setXstatus){
    printf("Type your coordinate X and Y\n");
    printf("ex) 1 2\n");
    int x,y;
    scanf("%d %d",&x,&y);
    setXstatus = setX(board->boardsize, x-1, y-1);
  }
}

void player2_game(struct FiveInRowField *board){
  print_board(board->boardsize);
  printf("Player 2, it's your turn!\n");
  bool setXstatus = false;
  while(!setXstatus){
    printf("Type your coordinate X and Y\n");
    printf("ex) 1 2\n");
    int x,y;
    scanf("%d %d",&x,&y);
    setXstatus = setO(board->boardsize, x-1, y-1);
  }
}

void computer_game(struct FiveInRowField *board){
  print_board(board->boardsize);
  printf("Computer's turn!\n");

  int greatestXRowsCount = 0;
  int greatestORowsCount = 0;
  int greatestXRowsYCord = -1;
  int greatestXRowsXCord = -1;
  int greatestORowsYCord = -1;
  int greatestORowsXCord = -1;
  for(int x = 0; x < 15; ++x) {
    int xRowsCount = 0;
    int oRowsCount = 0;
    for(int y = 0; y < 15; ++y) {
      if(board->boardsize[y][x] == 'X') {
        xRowsCount++;
        oRowsCount = 0;
      }
      else if(board->boardsize[y][x] == 'O') {
        oRowsCount++;
        xRowsCount = 0;
      }

        if(xRowsCount > greatestXRowsCount) {
          greatestXRowsCount = xRowsCount;
          greatestXRowsYCord = y;
          greatestXRowsXCord = x;

          if(y - xRowsCount >= 0) {
            if(y < 14) {
              if(board->boardsize[y - xRowsCount][x] == 'O' && board->boardsize[y + 1][x] == 'O') {
                greatestXRowsCount = 0;
                greatestXRowsYCord = -1;
                greatestXRowsXCord = -1;
              }
            }
            else if(y == 14) {
              if(board->boardsize[y - xRowsCount][x] == 'O') {
                greatestXRowsCount = 0;
                greatestXRowsYCord = -1;
                greatestXRowsXCord = -1;
              }
            }
          }
          else if(y - xRowsCount < 0) {
              if(board->boardsize[y - xRowsCount][x] == 'O') {
                greatestXRowsCount = 0;
                greatestXRowsYCord = -1;
                greatestXRowsXCord = -1;
              }
          }

        }

        if(oRowsCount > greatestORowsCount) {
          greatestORowsCount = oRowsCount;
          greatestORowsYCord = y;
          greatestORowsXCord = x;


          if(y - oRowsCount >= 0) {
            if(y < 14) {
              if(board->boardsize[y - oRowsCount][x] == 'X' && board->boardsize[y + 1][x] == 'X') {
                greatestXRowsCount = 0;
                greatestORowsYCord = -1;
                greatestORowsXCord = -1;
              }
            }
            else if(y == 14) {
              if(board->boardsize[y - oRowsCount][x] == 'X') {
                greatestXRowsCount = 0;
                greatestORowsYCord = -1;
                greatestORowsXCord = -1;
              }
            }
          }
          else if(y - oRowsCount < 0) {
              if(board->boardsize[y - oRowsCount][x] == 'X') {
                greatestXRowsCount = 0;
                greatestORowsYCord = -1;
                greatestORowsXCord = -1;
              }
          }
        }

    }

  }


  if(greatestORowsCount > greatestXRowsCount) {
    bool hasSetted = false;
    //printf("greatestORowsCount > greatestXRowsCount\n");
    //printf("greatestORowsCount: %d, greatestXRowsCount: %d\n", greatestORowsCount, greatestXRowsCount);
    // place O to up position if it is settable
    hasSetted = setO(board->boardsize, greatestORowsYCord - greatestORowsCount, greatestORowsXCord);
    // if has been setted then finish process
    if(hasSetted) {
      return;
    }
    else if(!hasSetted) {
      // place O to down position if it is settable
      hasSetted = setO(board->boardsize, greatestORowsYCord + 1, greatestORowsXCord);

      // if has been setted then finish process
      if(hasSetted) {
        return;
      }
    }
  }
  else if(greatestORowsCount < greatestXRowsCount) {
    bool hasSetted = false;
   // printf("greatestORowsCount < greatestXRowsCount\n");
   // printf("greatestORowsCount: %d, greatestXRowsCount: %d\n", greatestORowsCount, greatestXRowsCount);
    // place O to up position if it is settable
    hasSetted = setO(board->boardsize, greatestXRowsYCord - greatestXRowsCount, greatestXRowsXCord);
    // if has been setted then finish process
    if(hasSetted) {
      return;
    }
    else if(!hasSetted) {
      // place O to down position if it is settable
      hasSetted = setO(board->boardsize, greatestXRowsYCord + 1, greatestXRowsXCord);

      // if has been setted then finish process
      if(hasSetted) {
        return;
      }
    }
  }
  else if(greatestORowsCount == greatestXRowsCount){
    bool hasSetted = false;
    //printf("greatestORowsCount == greatestXRowsCount\n");
    //printf("greatestORowsCount: %d, greatestXRowsCount: %d\n", greatestORowsCount, greatestXRowsCount);
    // place O to up position if it is settable
    hasSetted = setO(board->boardsize, greatestORowsYCord - greatestORowsCount, greatestORowsXCord);
    // if has been setted then finish process
    if(hasSetted) {
      return;
    }
    else if(!hasSetted) {
      // place O to down position if it is settable
      hasSetted = setO(board->boardsize, greatestORowsYCord + 1, greatestORowsXCord);

      // if has been setted then finish process
      if(hasSetted) {
        return;
      }
    }
  }

  //printf("none of above are settable \n");
  //printf("greatestORowsCount: %d, greatestXRowsCount: %d\n", greatestORowsCount, greatestXRowsCount);

  // none of above are settable then place it randomly
  bool hasSetted = false;
  while(!hasSetted) {
    int randY = rand() % 3;
    int randX = rand() % 3;
    hasSetted = setO(board->boardsize, randY, randX);
  }
}

//Decide the turn of each player (swap function)
void Turn_decision(PLAYER1_TURN *player1, PLAYER2_TURN *player2){
  if(*player1 == PLAYER1_GameState){
    *player1 = PLAYER1_StartState;
    *player2 = PLAYER2_GameState;
  }
  else if(*player2 == PLAYER2_GameState){
    *player2 = PLAYER2_StartState;
    *player1 = PLAYER1_GameState;
  }
}

//PVP mode
void PVP_mode(){
  struct FiveInRowField board;
  display();
  set_board(board.boardsize);
  PLAYER1_TURN player1_turn = PLAYER1_GameState;
  PLAYER2_TURN player2_turn = PLAYER2_StartState;
  int winner = -1;
  while(winner == -1){
    if(player1_turn == PLAYER1_GameState){
      player1_game(&board);
    }
    else if(player2_turn == PLAYER2_GameState){
      player2_game(&board);
    }
    Turn_decision(&player1_turn, &player2_turn);
    winner = CheckWin(board.boardsize);
    }

    print_board(board.boardsize);
    if(winner == PLAYER1_WIN){
      printf("Player 1 win!\n");
    }else if(winner == PLAYER2_WIN){
      printf("Player 2 win!\n");
  }
}


void PVE_mode(){
 struct FiveInRowField board;
  display();
  set_board(board.boardsize);
  PLAYER1_TURN player1_turn = PLAYER1_GameState;
  PLAYER2_TURN computer_turn = PLAYER2_StartState;
  int winner = -1;
  while(winner == -1){
    if(player1_turn == PLAYER1_GameState){
      player1_game(&board);
    }
    else if(computer_turn == PLAYER2_GameState){
      computer_game(&board);
    }
    Turn_decision(&player1_turn, &computer_turn);
    winner = CheckWin(board.boardsize);
    }

    print_board(board.boardsize);
    if(winner == PLAYER1_WIN){
      printf("Player 1 win!\n");
    }else if(winner == PLAYER2_WIN){
      printf("Computer win!\n");
  }
}

void main_loop(){
  SELECT_MODE choose_mode = select_mode();

  if(choose_mode == 1){
    printf("Here comes a new player!\n");
    PVP_mode();
  }
  else if(choose_mode == 2){
    printf("Computer is ready to go!\n");
    PVE_mode();
  }
}

int main(){
  main_loop();

  return 0;
}

