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
void GameManager::Instructions()
{
    cout << "\nWelcome to Rohith's CONNECT-4 Game!\n";
    cout << "***********************************\n";
    cout << "\nInstructions";
    cout << "\n************\n";
    cout << "\nThe game is played on a vertical board that has seven columns and six rows. \nThe board is initially empty, with each column being able to hold up to six discs. \nTwo players take turns dropping their colored discs into the board from the top of the columns, with the discs falling to the lowest available position in the column. \nThe objective of the game is to be the first player to connect four of their own colored discs vertically, horizontally, or diagonally. \nOnce a player has connected four discs, they win the game. \nIf all of the columns are filled without either player connecting four discs, the game ends in a draw. \nPlayer 1 drops red (R) discs and Player 2 drops blue (B) discs.\n";
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
    cout << "\n ";
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        cout << i + 1 << " ";
    }
    cout << endl;
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
        delete[] board[i];
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
    p1Turn ? tempToken = Red : tempToken = Blue;
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
void GameManager::CheckDraw()
{
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        if (contents[i] != MAX_ROWS)
            return;
    }
    SetGameState(Draw);
    return;
}
bool GameManager::CheckHorizontal(int row, int col, Token currentToken)
{
    int count = 0;
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        if (board[row][i].GetToken() == currentToken)
            count++;
        else
            count = 0;
        if (count == WIN_COUNT)
            return true;
    }
    return false;
}
bool GameManager::CheckVertical(int row, int col, Token currentToken)
{
    int count = 0;
    for (int i = 0; i < MAX_ROWS; i++)
    {
        if (board[i][col].GetToken() == currentToken)
            count++;
        else
            count = 0;
        if (count == WIN_COUNT)
            return true;
    }
    return false;
}
bool GameManager::CheckDiagonal(int row, int col, Token currentToken)
{
    int count = 0;
    for (int i = row, j = col; i > 0 && j > 0; i--, j--)
    {
        if (board[i][j].GetToken() == currentToken)
            count++;
        else
            break;
        if (count == WIN_COUNT)
            return true;
    }
    if (count != 0)
        count--;
    for (int i = row, j = col; i < MAX_ROWS && j < MAX_COLUMNS; i++, j++)
    {
        if (board[i][j].GetToken() == currentToken)
            count++;
        else
            break;
        if (count == WIN_COUNT)
            return true;
    }
    count = 0;
    for (int i = row, j = col; i >= 0 && j < MAX_COLUMNS; i--, j++)
    {
        if (board[i][j].GetToken() == currentToken)
            count++;
        else
            break;
        if (count == WIN_COUNT)
            return true;
    }
    if (count != 0)
        count--;
    for (int i = row, j = col; i < MAX_ROWS && j >= 0; i++, j--)
    {
        if (board[i][j].GetToken() == currentToken)
            count++;
        else
            break;
        if (count == WIN_COUNT)
            return true;
    }
    return false;
}
bool GameManager::CheckWin(int row, int col, Token currentToken)
{
    if (CheckHorizontal(row, col, currentToken) || CheckVertical(row, col, currentToken) || CheckDiagonal(row, col, currentToken))
        return true;
    else
        return false;
}