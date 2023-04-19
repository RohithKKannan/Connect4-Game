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
    int *contents;

public:
    GameManager();
    void InsertToken(int column, Token token);
    void DisplayBoard();
    ~GameManager();
};