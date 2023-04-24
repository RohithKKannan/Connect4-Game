#include "connect.h"
using namespace std;
Board::Board()
{
    contents = new int[MAX_COLUMNS]();
    board = new Cell *[MAX_ROWS];
    for (int i = 0; i < MAX_ROWS; i++)
    {
        board[i] = new Cell[MAX_COLUMNS];
    }
}
Board::~Board()
{
    delete contents;
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}
bool Board::InsertToken(int column, bool p1Turn)
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
    contents[column]++;
    return true;
}
void Board::DisplayBoard()
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
bool Board::CheckHorizontal(int row, int col, Token currentToken)
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
bool Board::CheckVertical(int row, int col, Token currentToken)
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
bool Board::CheckDiagonal(int row, int col, Token currentToken)
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
bool Board::CheckDraw()
{
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        if (contents[i] != MAX_ROWS)
            return false;
    }
    return true;
}
