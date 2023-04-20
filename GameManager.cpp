#include "connect.h"
using namespace std;
GameManager::GameManager()
{
    p1Turn = true;
    SetGameState(Playing);
    contents = new int[MAX_COLUMNS]();
    board = new Cell *[MAX_ROWS];
    for (int i = 0; i < MAX_ROWS; i++)
    {
        board[i] = new Cell[MAX_COLUMNS];
    }
}
bool GameManager::IsPlayer1()
{
    return p1Turn;
}
void GameManager::ChangeTurn()
{
    p1Turn = !p1Turn;
}
void GameManager::SetGameState(GameState _gameState)
{
    gameState = _gameState;
}
GameState GameManager::GetGameState()
{
    return gameState;
}
void GameManager::DisplayBoard()
{
    for (int i = 0; i < MAX_ROWS; i++)
    {
        for (int j = 0; j < MAX_COLUMNS; j++)
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
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        delete board[i];
    }
    delete[] board;
}
bool GameManager::InsertToken(int column, bool p1Turn)
{
    if (contents[column] == MAX_ROWS)
    {
        cout << "\nColumn is full!";
        return false;
    }
    Token tempToken;
    if (p1Turn)
        tempToken = Red;
    else
        tempToken = Blue;
    // p1Turn ? tempToken = Red : tempToken = Blue;
    if (board[(MAX_ROWS - 1) - contents[column]][column].GetToken() == Empty)
        board[(MAX_ROWS - 1) - contents[column]][column].SetToken(tempToken);
    if (CheckWin((MAX_ROWS - 1) - contents[column], column, tempToken))
    {
        if (p1Turn)
            SetGameState(RedWin);
        else
            SetGameState(BlueWin);
        return true;
    }
    contents[column]++;
    return true;
}
bool GameManager::CheckDraw()
{
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        if (contents[i] != MAX_ROWS)
            return false;
    }
    SetGameState(Draw);
    return true;
}
bool GameManager::CheckWin(int row, int col, Token currentToken)
{
    int count = 0;
    // Check horizontal
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        if (board[row][i].GetToken() == currentToken)
            count++;
        else
            count = 0;
        if (count == WIN_COUNT)
            return true;
    }
    // Check vertical
    count = 0;
    for (int i = 0; i < MAX_ROWS; i++)
    {
        if (board[i][col].GetToken() == currentToken)
            count++;
        else
            count = 0;
        if (count == WIN_COUNT)
            return true;
    }
    // Check LRDiagonal
    count = 0;
    // // Upper half
    for (int i = row, j = col; i > 0 && j > 0; i--, j--)
    {
        if (board[i][j].GetToken() == currentToken)
            count++;
        if (count == WIN_COUNT)
            return true;
    }
    count--;
    // // Lower half
    for (int i = row, j = col; i < MAX_ROWS && j < MAX_COLUMNS; i++, j++)
    {
        if (board[i][j].GetToken() == currentToken)
            count++;
        if (count == WIN_COUNT)
            return true;
    }
    // Check RLDiagonal
    count = 0;
    // // Upper half
    for (int i = row, j = col; i >= 0 && j < MAX_COLUMNS; i--, j++)
    {
        if (board[i][j].GetToken() == currentToken)
            count++;
        if (count == WIN_COUNT)
            return true;
    }
    count--;
    // // Lower half;
    for (int i = row, j = col; i < MAX_ROWS && j >= 0; i++, j--)
    {
        if (board[i][j].GetToken() == currentToken)
            count++;
        if (count == WIN_COUNT)
            return true;
    }
    return false;
}