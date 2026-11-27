
#include <iostream>
#include <cstdlib>
using namespace std;

// Global array representing the game board
char board[9];

// Global variables for game statistics
int gamesPlayed = 0;
int playerXWins = 0;
int playerOWins = 0;
int draws = 0;

// Function prototypes
void initializeBoard();
void displayBoard();
void makeMove(char player);
bool checkWinner(char player);
bool checkDraw();
void playGame();
void displayStatistics();

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

    // Display final game statistics
    displayStatistics();

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

// Display game statistics
void displayStatistics()
{
    cout << "\n===== GAME STATISTICS =====\n";
    cout << "Total games played: " << gamesPlayed << endl;
    cout << "Player X wins: " << playerXWins << endl;
    cout << "Player O wins: " << playerOWins << endl;
    cout << "Number of draws: " << draws << endl;
    cout << "===========================\n";
}

// Main game function
void playGame()
{
    char currentPlayer = 'X';

    initializeBoard();

    // Increase total games played
    gamesPlayed++;

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

            // Update winner statistics
            if (currentPlayer == 'X')
            {
                playerXWins++;
            }
            else
            {
                playerOWins++;
            }

            break;
        }

        if (checkDraw())
        {
            cout << "The game is a DRAW!\n";

            // Update draw statistics
            draws++;

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
