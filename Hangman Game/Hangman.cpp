
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

// Function to draw the Hangman
void drawHangman(int wrongGuesses, int maxTries) {

    // Convert incorrect guesses into 5 drawing stages
    int stage = (wrongGuesses * 5) / maxTries;

    cout << "\n  +----+" << endl;
    cout << "  |    |" << endl;

    // Head
    cout << "  |    ";
    if (stage >= 1)
        cout << "O";
    cout << endl;

    // Body and arms
    cout << "  |   ";
    if (stage >= 3)
        cout << "/";
    else
        cout << " ";

    if (stage >= 2)
        cout << "|";
    else
        cout << " ";

    if (stage >= 4)
        cout << "\\";
    cout << endl;

    // Legs
    cout << "  |   ";
    if (stage >= 5)
        cout << "/ \\";
    cout << endl;

    cout << "  |" << endl;
    cout << "__|__" << endl;
}

// Function to display the hidden word
void displayWord(const string& word) {

    for (int i = 0; i < word.length(); i++) {
        cout << word[i] << " ";
    }

    cout << endl;
}

int main() {

    srand(time(0));

    string words[5] = {
        "apple", "peach", "banana",
        "strawberry", "mango"
    };

    char playAgain = 'Y';

    while (toupper(playAgain) == 'Y') {

        int maxTries;
        int difficulty;

        // Select difficulty
        do {
            system("cls");

            cout << "========================" << endl;
            cout << "      HANGMAN GAME      " << endl;
            cout << "========================" << endl;

            cout << "\nSelect Difficulty:" << endl;
            cout << "1. Easy   (8 guesses)" << endl;
            cout << "2. Medium (6 guesses)" << endl;
            cout << "3. Hard   (4 guesses)" << endl;

            cout << "\nEnter your choice: ";
            cin >> difficulty;

            if (difficulty < 1 || difficulty > 3) {
                cout << "\nInvalid choice! Try again.";
                cin.clear();
                cin.ignore(1000, '\n');
                cin.get();
            }

        } while (difficulty < 1 || difficulty > 3);

        // Set maximum guesses
        if (difficulty == 1)
            maxTries = 8;
        else if (difficulty == 2)
            maxTries = 6;
        else
            maxTries = 4;

        // Select a random word
        string word = words[rand() % 5];

        string hiddenWord(word.length(), '_');
        string guessedLetters = "";
        string wrongLetters = "";

        int wrongGuesses = 0;

        // Main game loop
        while (wrongGuesses < maxTries &&
               hiddenWord != word) {

            system("cls");

            cout << "========================" << endl;
            cout << "      HANGMAN GAME      " << endl;
            cout << "========================" << endl;

            cout << "\nDifficulty: ";

            if (difficulty == 1)
                cout << "Easy";
            else if (difficulty == 2)
                cout << "Medium";
            else
                cout << "Hard";

            cout << "\n\nWord: ";
            displayWord(hiddenWord);

            cout << "\nIncorrect guesses: "
                 << wrongGuesses << "/" << maxTries << endl;

            cout << "Wrong letters: "
                 << wrongLetters << endl;

            drawHangman(wrongGuesses, maxTries);

            string input;

            cout << "\nEnter one letter: ";
            cin >> input;

            // Validate input
            if (input.length() != 1 ||
                !isalpha(static_cast<unsigned char>(input[0]))) {

                cout << "\nInvalid input! Enter only one letter.";
                cin.ignore(1000, '\n');
                cin.get();
                continue;
            }

            char guess = tolower(
                static_cast<unsigned char>(input[0])
            );

            // Check repeated guesses
            if (guessedLetters.find(guess) != string::npos) {

                cout << "\nYou already guessed that letter!";
                cin.ignore(1000, '\n');
                cin.get();
                continue;
            }

            guessedLetters += guess;

            bool found = false;

            // Check the guessed letter
            for (int i = 0; i < word.length(); i++) {

                if (word[i] == guess) {
                    hiddenWord[i] = guess;
                    found = true;
                }
            }

            if (found) {
                cout << "\nCorrect guess!";
            }
            else {
                wrongGuesses++;

                wrongLetters += guess;
                wrongLetters += " ";

                cout << "\nWrong guess!";
            }

            cin.ignore(1000, '\n');
            cin.get();
        }

        // Display final result
        system("cls");

        cout << "========================" << endl;
        cout << "       GAME OVER        " << endl;
        cout << "========================" << endl;

        cout << "\nCorrect word: " << word << endl;

        drawHangman(wrongGuesses, maxTries);

        if (hiddenWord == word) {
            cout << "\nCongratulations! YOU WIN!" << endl;
        }
        else {
            cout << "\nSorry! YOU LOSE!" << endl;
        }

        cout << "\nWould you like to play again? (Y/N): ";
        cin >> playAgain;
    }

    cout << "\nThank you for playing Hangman!" << endl;

    return 0;
}
