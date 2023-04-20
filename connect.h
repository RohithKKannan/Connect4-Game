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
class GameManager
{
    Cell **board;
    int *contents;
    bool p1Turn;
    GameState gameState;

public:
    GameManager();
    bool IsPlayer1();
    void ChangeTurn();
    void SetGameState(GameState);
    GameState GetGameState();
    bool InsertToken(int, bool);
    void DisplayBoard();
    bool CheckWin(int, int, Token);
    bool CheckDraw();
    ~GameManager();
};