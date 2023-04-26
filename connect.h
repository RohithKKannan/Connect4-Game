#include <iostream>
#define MAX_ROWS 6
#define MAX_COLUMNS 7
#define WIN_COUNT 4
enum GameState
{
    Playing,
    Draw,
    RedWin,
    BlueWin
};
enum Token
{
    Empty,
    Red,
    Blue
};
class Cell
{
    Token token;

public:
    Cell();
    Token GetToken();
    void SetToken(Token token);
};
class Board
{
    Cell **board;
    int *contents;

public:
    Board();
    bool InsertToken(int, bool);
    void DisplayBoard();
    bool CheckHorizontal(int, int, Token);
    bool CheckVertical(int, int, Token);
    bool CheckDiagonal(int, int, Token);
    bool CheckContentsMax();
    ~Board();
};
class GameManager
{
    Board *Connect4Board;
    bool p1Turn;
    GameState gameState;

    bool GameLoop();
    void Instructions();
    bool IsPlayer1();
    void ChangeTurn();
    void SetGameState(GameState);
    GameState GetGameState();
    void DisplayBoard();
    bool InsertToken();
    bool CheckDraw();
    bool CheckWin(int, int, Token);

public:
    GameManager();
    void StartGame();
    ~GameManager();
};