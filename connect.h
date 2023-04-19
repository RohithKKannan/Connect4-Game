#include <iostream>
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

public:
    GameManager();
    void DisplayBoard();
    ~GameManager();
};