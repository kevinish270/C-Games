#include <iostream>
#include <cstdlib>
using namespace std;

// Global array representing the game board
char board[9];

// Function prototypes
void initializeBoard();
void displayBoard();
void makeMove(char player);
bool checkWinner(char player);
bool checkDraw();
void playGame();

int main()
{
    char choice;

    do
    {
        playGame();

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> choice;

    } while (choice == 'Y' || choice == 'y');

    cout << "\nThank you for playing Tic-Tac-Toe!\n";

    return 0;
}

// Initialize the board with numbers 1 to 9
void initializeBoard()
{
    for (int i = 0; i < 9; i++)
    {
        board[i] = '1' + i;
    }
}

// Display the game board
void displayBoard()
{
    system("cls");
    cout << "\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
    cout << "\n";
}

// Allow a player to make a move
void makeMove(char player)
{
    int position;

    while (true)
    {
        cout << "Player " << player << ", enter a position (1-9): ";
        cin >> position;

        // Validate the position
        if (cin.fail())
        {
            cout << "Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (position < 1 || position > 9)
        {
            cout << "Invalid position! Choose between 1 and 9.\n";
        }
        else if (board[position - 1] == 'X' ||
                 board[position - 1] == 'O')
        {
            cout << "That position is already taken! Try again.\n";
        }
        else
        {
            board[position - 1] = player;
            break;
        }
    }
}

// Check whether a player has won
bool checkWinner(char player)
{
    // All possible winning combinations
    int winningPositions[8][3] =
    {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}
    };

    for (int i = 0; i < 8; i++)
    {
        if (board[winningPositions[i][0]] == player &&
            board[winningPositions[i][1]] == player &&
            board[winningPositions[i][2]] == player)
        {
            return true;
        }
    }

    return false;
}

// Check whether the game is a draw
bool checkDraw()
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i] != 'X' && board[i] != 'O')
        {
            return false;
        }
    }

    return true;
}

// Main game logic
void playGame()
{
    char currentPlayer = 'X';

    initializeBoard();

    cout << "\n===== TIC-TAC-TOE GAME =====\n";

    displayBoard();

    while (true)
    {
        makeMove(currentPlayer);

        displayBoard();

        if (checkWinner(currentPlayer))
        {
            cout << "Congratulations! Player "
                 << currentPlayer << " wins!\n";
            break;
        }

        if (checkDraw())
        {
            cout << "The game is a DRAW!\n";
            break;
        }

        // Switch players
        if (currentPlayer == 'X')
        {
            currentPlayer = 'O';
        }
        else
        {
            currentPlayer = 'X';
        }
    }
}