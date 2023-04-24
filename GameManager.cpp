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
void GameManager::DisplayBoard()
{
    Connect4Board->DisplayBoard();
}
GameManager::~GameManager()
{
    delete Connect4Board;
}