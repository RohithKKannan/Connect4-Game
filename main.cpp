#include <iostream>
#include "connect.h"
using namespace std;

int main()
{
    GameManager gameManager;
    gameManager.DisplayBoard();
    int col = 0;
    while (true)
    {
        if (gameManager.IsPlayer1())
            cout << "\nPlayer 1 enter a column no. : ";
        else
            cout << "\nPlayer 2 enter a column no. : ";
        cin >> col;
        if (!gameManager.InsertToken((col - 1), gameManager.IsPlayer1()))
        {
            gameManager.DisplayBoard();
            continue;
        }
        gameManager.DisplayBoard();
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