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
    // cout << "\nChecking Diagonal for ";
    // if (currentToken == Blue)
    //     cout << "Blue!\n";
    // else
    //     cout << "Red!\n";
    int count = 0;
    // cout << "\nLeft to Right Diagonal : \n";
    // cout << "Count : " << count << endl;
    for (int i = row, j = col; i > 0 && j > 0; i--, j--)
    {
        if (board[i][j].GetToken() == currentToken)
        {
            // cout << "Token found at row " << i + 1 << " and col " << j + 1 << endl;
            // cout << "Count : " << count + 1 << endl;
            count++;
        }
        else
        {
            // cout << "\tToken not found at row " << i + 1 << " and col " << j + 1 << endl;
            // cout << "\tBreak half\n\n";
            break;
        }
        if (count == WIN_COUNT)
        {
            // cout << "Count value is four! Winner found!\n";
            return true;
        }
    }
    if (count != 0)
    {
        // cout << "Decrement count to " << count - 1 << endl;
        count--;
    }
    for (int i = row, j = col; i < MAX_ROWS && j < MAX_COLUMNS; i++, j++)
    {
        if (board[i][j].GetToken() == currentToken)
        {
            // cout << "Token found at row " << i + 1 << " and col " << j + 1 << endl;
            // cout << "Count : " << count + 1 << endl;
            count++;
        }
        else
        {
            // cout << "\tToken not found at row " << i + 1 << " and col " << j + 1 << endl;
            // cout << "\tBreak half\n\n";
            break;
        }
        if (count == WIN_COUNT)
        {
            // cout << "Count value is four! Winner found!\n";
            return true;
        }
    }
    // cout << "\n\nRight to Left Diagonal : \n";
    // cout << "Count : " << count << endl;
    count = 0;
    for (int i = row, j = col; i >= 0 && j < MAX_COLUMNS; i--, j++)
    {
        if (board[i][j].GetToken() == currentToken)
        {
            // cout << "Token found at row " << i + 1 << " and col " << j + 1 << endl;
            // cout << "Count : " << count + 1 << endl;
            count++;
        }
        else
        {
            // cout << "\tToken not found at row " << i + 1 << " and col " << j + 1 << endl;
            // cout << "\tBreak half\n\n";
            break;
        }
        if (count == WIN_COUNT)
        {
            // cout << "Count value is four! Winner found!\n";
            return true;
        }
    }
    if (count != 0)
    {
        // cout << "Decrement count to " << count - 1 << endl;
        count--;
    }
    for (int i = row, j = col; i < MAX_ROWS && j >= 0; i++, j--)
    {
        if (board[i][j].GetToken() == currentToken)
        {
            // cout << "Token found at row " << i + 1 << " and col " << j + 1 << endl;
            // cout << "Count : " << count + 1 << endl;
            count++;
        }
        else
        {
            // cout << "\tToken not found at row " << i + 1 << " and col " << j + 1 << endl;
            // cout << "\tBreak half\n\n";
            break;
        }
        if (count == WIN_COUNT)
        {
            // cout << "Count value is four! Winner found!\n";
            return true;
        }
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