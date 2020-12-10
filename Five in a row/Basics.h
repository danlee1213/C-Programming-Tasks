typedef enum{
  PVP=1,
  PVE
}SELECT_MODE;

typedef enum{
  PLAYER1_StartState=1,
  PLAYER1_GameState,
  PLAYER1_EndState
}PLAYER1_TURN;

typedef enum{
  PLAYER2_StartState=4,
  PLAYER2_GameState,
  PLAYER2_EndState
}PLAYER2_TURN;

typedef enum{
  PLAYER1_WIN,
  PLAYER2_WIN
}WHO_WIN;
