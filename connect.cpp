#include "connect.h"
using namespace std;

Cell::Cell()
{
    token = Empty;
}
Token Cell::GetToken()
{
    return token;
}
void Cell::SetToken(Token token)
{
    this->token = token;
}
GameManager::GameManager()
{
    board = new Cell *[6];
    for (int i = 0; i < 6; i++)
    {
        board[i] = new Cell[7];
    }
}
void GameManager::DisplayBoard()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            switch (board[i][j].GetToken())
            {
            case Empty:
                cout << "| ";
                break;
            case Red:
                cout << "|R";
                break;
            case Blue:
                cout << "|B";
                break;
            }
        }
        cout << "|\n";
    }
}
GameManager::~GameManager()
{
    for (int i = 0; i < 7; i++)
    {
        delete board[i];
    }
    delete[] board;
}