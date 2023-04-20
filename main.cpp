#include <iostream>
#include "connect.h"
using namespace std;

int main()
{
    GameManager gameManager;
    gameManager.Instructions();
    gameManager.DisplayBoard();
    int col = 1;
    while (true)
    {
        do
        {
            if (col < 0 || col > MAX_COLUMNS)
                cout << "\nPlease enter valid input";
            if (gameManager.IsPlayer1())
                cout << "\nPlayer 1 enter a column no. (1 - 7) : ";
            else
                cout << "\nPlayer 2 enter a column no. (1 - 7) : ";
            cin >> col;
        } while (col < 0 || col > MAX_COLUMNS);
        if (!gameManager.InsertToken((col - 1), gameManager.IsPlayer1()))
        {
            gameManager.DisplayBoard();
            continue;
        }
        gameManager.DisplayBoard();
        gameManager.CheckDraw();
        if (gameManager.GetGameState() != Playing)
        {
            switch (gameManager.GetGameState())
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
            break;
        }
        gameManager.ChangeTurn();
    }
    cout << "\nThanks for playing :)\n";
    return 0;
}