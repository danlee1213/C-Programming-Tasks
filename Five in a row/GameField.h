#define ARR_SIZE_R 15 //Row size
#define ARR_SIZE_C 15 // Column Size
#define WIN_NUMBER 5   // Winning count

struct FiveInRowField{
  char boardsize[ARR_SIZE_R][ARR_SIZE_C];
  int index_row;
  int index_col;
  int index_cnt;
}board;

int display()
{
 puts("  =================================================");
 printf("\t Welcome to the Five in a Row Game (%d X %d)\n", ARR_SIZE_R, ARR_SIZE_C);
 puts("  =================================================\n");
 return 0;
}

int set_board(char gameboard[][ARR_SIZE_C]){
  for(board.index_row=0; board.index_row < ARR_SIZE_R; ++board.index_row){
    for(board.index_col=0; board.index_col < ARR_SIZE_C; ++board.index_col){
      gameboard[board.index_row][board.index_col] = '.';
    }
  }
  return 0;
}

//Print the number of the column and row of the board
int print_board(char gameboard[][ARR_SIZE_C]){
  puts("  -----------------------------------------");
   puts("\t\t\t   Game Situation");
   puts("  -----------------------------------------\n");

  //Print Column Number
   for(board.index_cnt=0; board.index_cnt <= ARR_SIZE_C; ++board.index_cnt){
     if(board.index_cnt == 0){
      printf("    ");
     } else if(board.index_cnt >= 10){
       printf("%3d ", board.index_cnt % 10);
     } else{
       printf("%3d ", board.index_cnt);
     }
   }
   puts("\n");

  //Print Row Number and board dots
   for(board.index_row=1; board.index_row <= ARR_SIZE_R; ++board.index_row){
     if(board.index_row >= 10){
       printf("%3d ", board.index_row % 10);
     } else{
       printf("%3d ", board.index_row);
     }

     for(board.index_col=0; board.index_col < ARR_SIZE_C; ++board.index_col){
      printf(" %2c ", gameboard[board.index_row-1][board.index_col]);
     }
     puts("\n");
   }
   return 0;
}

bool setX(char (*boardsize)[ARR_SIZE_C], int X, int Y){
  if(X < 0 || X >= 15 || Y < 0 || Y >= 15){
    printf("Coordinate range should be between 1 ~ 15\n");
    return false;
  }

  if(boardsize[X][Y] != '.'){
    printf("The area has been occupied!\n");
    return false;
  }

  boardsize[X][Y] = 'X';
  return true;
}

bool setO(char (*boardsize)[ARR_SIZE_C], int X, int Y){
  if(X < 0 || X >= 15 || Y < 0 || Y >= 15){
    printf("Coordinate range should be between 1 ~ 15\n");
    return false;
  }

  if(boardsize[X][Y] != '.'){
    printf("The area has been occupied!\n");
    return false;
  }

  boardsize[X][Y] = 'O';
  return true;
}

//Check winning conditions
int vertical_check(char (*boardsize)[ARR_SIZE_C]){

  //vertical checking
  for(int x=0; x < ARR_SIZE_R; ++x){
    int xColCount = 0;
    int oColCount = 0;

    for(int y=0; y < ARR_SIZE_C; ++y){
      if(boardsize[x][y] == 'X'){
        xColCount++;
        oColCount = 0;
      }
      else if(boardsize[x][y] == 'O'){
        oColCount++;
        xColCount = 0;
      }
      else if(boardsize[x][y] == '.'){
        xColCount = 0;
        oColCount = 0;
      }

      //printf("boardsize[%d][%d]: %c\n",x,y,boardsize[x][y]);
      // printf("Vercnt: %d\n",xColCount);

      if(xColCount == WIN_NUMBER){
        return PLAYER1_EndState;
      }
      else if(oColCount == WIN_NUMBER){
        return PLAYER2_EndState;

      }
    }

  }
  //None of them
  return -1;
}

int horizontal_check(char (*boardsize)[ARR_SIZE_C]){

  //horizontal checking
  for(int y=0; y < ARR_SIZE_C; ++y){
    int xRowCount = 0;
    int oRowCount = 0;

    for(int x=0; x < ARR_SIZE_R; ++x){
      if(boardsize[x][y] == 'X'){
        xRowCount++;
        oRowCount = 0;
      }
      else if(boardsize[x][y] == 'O'){
        oRowCount++;
        xRowCount = 0;
      }
      else if(boardsize[x][y] == '.'){
        xRowCount = 0;
        oRowCount = 0;
      }

      if(xRowCount == WIN_NUMBER){
        return PLAYER1_EndState;
      }
      else if(oRowCount == WIN_NUMBER){
        return PLAYER2_EndState;

      }
    }
     // printf("horcnt: %d\n",xRowCount);
  }
  //None of them
  return -1;
}

int diagonal1_check(char (*boardsize)[ARR_SIZE_C]){

  //diagonal1 checking(left upper)
   int xDiag1Count = 0;
   int oDiag1Count = 0;

  for(int x=0; x < ARR_SIZE_R; ++x){
    for(int y=0; y < ARR_SIZE_C; ++y){
      for(int pos = 0; pos < 5 && pos + x < ARR_SIZE_R && pos + y < ARR_SIZE_C; ++pos) {

        if(boardsize[x+pos][y+pos] == 'X') {
          xDiag1Count++;
          oDiag1Count = 0;
        }
        else if(boardsize[x+pos][y+pos] == 'O'){
        oDiag1Count++;
        xDiag1Count = 0;
        }
        else if(boardsize[x+pos][y+pos] == '.'){
          xDiag1Count = 0;
          oDiag1Count = 0;
        }

        if(xDiag1Count == WIN_NUMBER){
          return PLAYER1_EndState;
        }
        else if(oDiag1Count == WIN_NUMBER){
          return PLAYER2_EndState;
        }
      }
    }
     // printf("diag1cnt: %d\n",xDiag1Count);
  }
  //None of them
  return -1;
}

int diagonal2_check(char (*boardsize)[ARR_SIZE_C]){

  //diagonal2 checking(right upper)
   int xDiag2Count = 0;
   int oDiag2Count = 0;

  for(int x=0; x < ARR_SIZE_R; ++x){
    for(int y=0; y < ARR_SIZE_C; ++y){
      for(int pos = 0; pos < 5 && x + pos < ARR_SIZE_R && y - pos < ARR_SIZE_C; ++pos) {

        if(boardsize[x+pos][y-pos] == 'X') {
          xDiag2Count++;
          oDiag2Count = 0;
        }
        else if(boardsize[x+pos][y-pos] == 'O'){
        oDiag2Count++;
        xDiag2Count = 0;
        }
        else if(boardsize[x+pos][y-pos] == '.'){
          xDiag2Count = 0;
          oDiag2Count = 0;
        }
        if(xDiag2Count == WIN_NUMBER){
          return PLAYER1_EndState;
        }
        else if(oDiag2Count == WIN_NUMBER){
          return PLAYER2_EndState;
        }
      }
    }
     // printf("diag2cnt: %d\n",xDiag2Count);
  }

  //None of them
  return -1;
}

//Overall Check
int CheckWin(char (*boardsize)[ARR_SIZE_C]){

  vertical_check(boardsize);
  horizontal_check(boardsize);
  diagonal1_check(boardsize);
  diagonal2_check(boardsize);


  // printf("verticalresult: %d\n", vertical_check(board.boardsize));
  // printf("horizontalresult: %d\n", horizontal_check(board.boardsize));
  // printf("diag1result: %d\n", diagonal1_check(board.boardsize));
  // printf("diag2result: %d\n", diagonal2_check(board.boardsize));

  if(vertical_check(boardsize) == PLAYER1_EndState || horizontal_check(boardsize) == PLAYER1_EndState || diagonal1_check(boardsize) == PLAYER1_EndState || diagonal2_check(boardsize) == PLAYER1_EndState){
    return PLAYER1_WIN;
  }
  else if(vertical_check(boardsize) == PLAYER2_EndState || horizontal_check(boardsize) == PLAYER2_EndState || diagonal1_check(boardsize) == PLAYER2_EndState || diagonal2_check(boardsize) == PLAYER2_EndState){
    return PLAYER2_WIN;
  }

  return -1;
}

