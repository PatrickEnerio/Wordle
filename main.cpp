/*
*/
#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MAX_WORDS 10000
#define WORD_LENGTH 6 // 5 letters + null terminator

void displayHomeScreen();
void instructions(); 
bool readingFile(string& fileName, char words[MAX_WORDS][WORD_LENGTH], int& wordCount);
string chosenRandomWord(char words[MAX_WORDS][WORD_LENGTH], int wordCount);
void wordChecker(string chosenWord, string guess);
string toUpperCase(string str);

int main()
{
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    displayHomeScreen();
    
    char ch;
    cin >> ch;
    ch = toupper(ch);
    
    char words[MAX_WORDS][WORD_LENGTH];
    int wordCount = 0;
    string fileBank;
    
    while(ch != 'Q')
    {
        switch(ch)
        {
            case 'A':
                if(readingFile(fileBank, words, wordCount))
                {
                    string chosenWord = chosenRandomWord(words, wordCount);
                    string firstGuess;
                    int attempts = 0;

                    while(attempts < 6)
                    {
                        cout << "Please input your guess (" << (attempts + 1) << "/6):" << endl;
                        cin >> firstGuess;

                        // Convert guess to uppercase
                        firstGuess = toUpperCase(firstGuess);

                        if (firstGuess.length() != 5) {
                            cout << "Please enter a 5-letter word." << endl;
                            continue;
                        }

                        wordChecker(chosenWord, firstGuess);
                        
                        if (firstGuess == chosenWord) {
                            cout << "Congratulations! You've guessed the word!" << endl;
                            break;
                        }
                        
                        attempts++;
                    }

                    if(attempts == 6) {
                        cout << "Sorry, you've run out of attempts! The word was: " << chosenWord << endl;
                    }
                }
                break;
            case 'I':
                instructions();
                break;
            default:
                break;
        }
        
        displayHomeScreen();
        cin >> ch;
        ch = toupper(ch);
    }
    
    cout << "Thanks for playing!!!" << endl;

    return 0;
}

void displayHomeScreen()
{
    cout << "Wordle" << endl;
    cout << "------------------" << endl;
    cout << "Press 'A' to start" << endl;
    cout << "Press 'I' for instructions" << endl;
    cout << "Press 'Q' to Quit" << endl;
}

void instructions()
{
    cout << "\nThe aim of the game is to correctly guess a randomly selected word from a bank" << endl;
    cout << "within a given number of attempts. You'll receive feedback based on your guesses:" << endl;
    cout << " - If a letter is in the correct position, it will be shown in uppercase." << endl;
    cout << " - If a letter is in the word but in the wrong position, it will be shown in lowercase." << endl;
    cout << " - If a letter is not in the word, it will be omitted." << endl;
    cout << "You will have 6 attempts to guess the word. Good luck!" << endl;
}

bool readingFile(string& fileName, char words[MAX_WORDS][WORD_LENGTH], int& wordCount)
{
    cout << "Please enter word bank file:" << endl;
    cin >> fileName;

    ifstream file(fileName);
    
    if (!file.is_open())
    {
        cout << "Error opening file, " << fileName << ". Please reinput file name: " << endl;
        return false; // Return false if the file cannot be opened
    }    
    
    while (wordCount < MAX_WORDS && file >> words[wordCount])
    {
        wordCount++;
    } 
    
    file.close();
    return true;
}

string chosenRandomWord(char words[MAX_WORDS][WORD_LENGTH], int wordCount)
{
    int randomChosenWord = rand() % wordCount;
    string chosenUpperCase = toUpperCase(string(words[randomChosenWord]));
    
    return chosenUpperCase;
}

void wordChecker(string chosenWord, string guess)
{
    string result = "";

    for (int i = 0; i < chosenWord.length(); i++)
    {
        if (guess[i] == chosenWord[i]) {
            result += toupper(guess[i]); // Correct letter in the correct position
        } else if (chosenWord.find(guess[i]) != string::npos) {
            result += tolower(guess[i]); // Correct letter in the wrong position
        } else {
            result += '.'; // Letter not in the word
        }
    }

    cout << "Result: " << result << endl; // Display the result of the guess
}

string toUpperCase(string str)
{
    for (char& c : str) 
    {
        c = toupper(c); // Convert each character to uppercase
    }
    return str; // Return the modified string
}
