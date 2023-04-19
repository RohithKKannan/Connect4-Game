#include "connect.h"
using namespace std;
GameManager::GameManager()
{
    contents = new int[7]();
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
    delete contents;
    for (int i = 0; i < 7; i++)
    {
        delete board[i];
    }
    delete[] board;
}
void GameManager::InsertToken(int column, Token token)
{
    if (board[token][6 - contents[token]].GetToken() == Empty)
        board[token][6 - contents[token]].SetToken(token);
    contents[token]++;
}