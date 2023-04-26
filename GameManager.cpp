#include "connect.h"
using namespace std;
GameManager::GameManager()
{
    p1Turn = true;
    SetGameState(Playing);
    Connect4Board = new Board();
}
void GameManager::Instructions()
{
    cout << "\nWelcome to Rohith's CONNECT-4 Game!\n";
    cout << "***********************************\n";
    cout << "\nInstructions";
    cout << "\n************\n";
    cout << "\nThe game is played on a vertical board that has seven columns and six rows. \nThe board is initially empty, with each column being able to hold up to six discs. \nTwo players take turns dropping their colored discs into the board from the top of the columns, with the discs falling to the lowest available position in the column. \nThe objective of the game is to be the first player to connect four of their own colored discs vertically, horizontally, or diagonally. \nOnce a player has connected four discs, they win the game. \nIf all of the columns are filled without either player connecting four discs, the game ends in a draw. \nPlayer 1 drops red (R) discs and Player 2 drops blue (B) discs.\n";
}
void GameManager::StartGame()
{
    Instructions();
    bool flag = true;
    while (flag)
    {
        flag = GameLoop();
    }
    cout << "\nThanks for playing :)\n";
}
bool GameManager::GameLoop()
{

    if (!InsertToken())
    {
        DisplayBoard();
        return true;
    }
    DisplayBoard();

    ChangeTurn();
    return true;
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
bool GameManager::CheckWin(int row, int col, Token currentToken)
{
    if (Connect4Board->CheckHorizontal(row, col, currentToken) || Connect4Board->CheckVertical(row, col, currentToken) || Connect4Board->CheckDiagonal(row, col, currentToken))
        return true;
    else
        return false;
}
bool GameManager::CheckDraw()
{
    return Connect4Board->CheckContentsMax();
}
bool GameManager::InsertToken()
{
    int col = 1;
    do
    {
        if (col < 1 || col > MAX_COLUMNS)
            cout << "\nPlease enter valid input";
        if (IsPlayer1())
            cout << "\nPlayer 1 enter a column no. (1 - 7) : ";
        else
            cout << "\nPlayer 2 enter a column no. (1 - 7) : ";
        cin >> col;
    } while (col < 1 || col > MAX_COLUMNS);
    return Connect4Board->InsertToken(col, p1Turn);
}
bool GameManager::CheckWinDraw()
{
    CheckDraw();
    if (GetGameState() != Playing)
    {
        switch (GetGameState())
        {
        case RedWin:
            cout << "\nPlayer 1 has won!\n";
            break;
        case BlueWin:
            cout << "\nPlayer 2 has won!\n";
            break;
        case Draw:
            cout << "\nAll columns have been filled! The game is a draw!\n";
            break;
        }
        return false;
    }
}
void GameManager::DisplayBoard()
{
    Connect4Board->DisplayBoard();
}
GameManager::~GameManager()
{
    delete Connect4Board;
}