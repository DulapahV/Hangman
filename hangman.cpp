// Written by Dulapah Vibulsanti (64011388)
// Hidden Hangman Project
// See README.txt for more information.

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>
#include <time.h>
#include <string>

using namespace std;

// function prototype
string GetWord(unsigned int num); // get a random word from word.txt

string DisplayCorrect(string ref, string hidden, char show); // print out "_" and/or corrected guess

fstream &ReadLine(fstream& file, unsigned int num); // read a specific line in word.txt and return the text in that line

int GetRandInt(); // generate a random integer

void HangMan(int num); // print out a Hangman

char GetUsin(); // get user input

bool CheckUsin(string ref, char letter); // check whether user's guess is correct

int life = 10; // player's life (max = 10)

// main driver code
int main() {
    string generatedWord = GetWord(GetRandInt()); // Get a word
    int generatedWordLength = generatedWord.length();

    cout << "Choosen word is " << generatedWord << endl; // DEBUG

    HangMan(life);   
    cout << "Remaining Life: " << life << endl << endl;

    string allDashed; // Create a "_" to show user
    for (int i = 0; i < generatedWordLength; i++) {
        allDashed[i] = '_';
        cout << allDashed[i] << " ";
    }
    cout << endl << endl;

    // store all unique alphabet from generatedWord into a vector 
    vector<char> uniqueKey(generatedWord.begin(), generatedWord.end());
    sort(uniqueKey.begin(), uniqueKey.end());
    uniqueKey.erase(unique(uniqueKey.begin(), uniqueKey.end()), uniqueKey.end());
    int charLeft = uniqueKey.size(); // store number of characters not yet guessed

    vector<char> repeat;
    while (life > 0 ) {
        if (charLeft != 0) { // check whether there are characters not yet guessed
            char usin =  GetUsin();
            string display = DisplayCorrect(generatedWord, allDashed, usin);
            if (CheckUsin(generatedWord, usin)) { // check whether user's guess is correct
                bool enableDsp = true; // enable/disable display of correct guess
                for (int i = 0; i < repeat.size(); i++) { // Check whether user's guess is repeated
                    if (usin == repeat[i]) {
                        life--;
                        cout << "Repeated guess!" << endl;
                        enableDsp = false;
                        break;
                    }
                }
                repeat.push_back(usin);
                HangMan(life);
                cout << "Remaining Life: " << life << endl << endl;
                if (enableDsp) {
                    for (int i = 0; i < generatedWordLength; i++) { // print "_" and correct letter
                        cout << display[i] << " "; 
                    }
                    charLeft--;
                }
                else {
                    for (int i = 0; i < generatedWordLength; i++) { // print "_"
                        cout << allDashed[i] << " ";
                    }
                }
                cout << endl << endl;
            }
            else {
                life--;
                if (life != 0) { // check whether life != 0
                    cout << "Incorrect guess!" << endl;
                    HangMan(life);
                    cout << "Remaining Life: " << life << endl << endl;
                    for (int i = 0; i < generatedWordLength; i++) { // print "_"
                        cout << display[i] << " ";
                    }
                }
                else {
                    cout << "Game over!" << endl;
                    HangMan(life);
                    cout << "Remaining Life: " << life << endl << endl;
                    for (int i = 0; i < generatedWordLength; i++) {
                        cout << generatedWord[i] << " ";
                    }
                }
                cout << endl << endl;
            }
        }
        else {
            system("cls");
            HangMan(life);
            cout << "Remaining Life: " << life << endl << endl;
            for (int i = 0; i < generatedWordLength; i++) {
                cout << generatedWord[i] << " ";
            }
            cout << endl << endl;
            cout << "You win!" << endl;
            system("pause");
            return 0;
        }

    }
    cout << "You loose :(" << endl;
    system("pause");
    return 0;
}

// function
fstream &ReadLine(fstream& file, unsigned int num) {
    file.seekg(ios::beg);
    for (int i = 0; i < num - 1; i++) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return file;
}

int GetRandInt() {
    // Get 100 random integers by using hardware as a seed and store them into an array. 
    // Then choose an integer from that array by using rand() and time as a seed.

    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(3, 215); // define the range
    const int size = 100; // specifies the number of random numbers to generate
    int randArr[size];
    for (int i = 0; i < size; i++) {
        randArr[i] = distr(gen); // generate numbers and stored them to randArr array
    }
    
    srand((unsigned)time(0)); // seed the generator
    int randChoose = rand() % 100; // generate number
    int randFinal = randArr[randChoose]; // get a final random number
    return randFinal;
}

string GetWord(unsigned int num) {
    fstream file("word.txt");
    ReadLine(file, num);
    string word;
    file >> word;
    return word;
}

// hangman ASCII art edited from https://gist.github.com/chrishorton/8510732aa9a80a03c829b09f12e20d9c
void HangMan(int num) {
    switch (num) {
        case 10:
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "         " << endl;
            break;
        case 9:
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "=========" << endl;
            break;
        case 8:
            cout << "       " << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 7:
            cout << "  +---+" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 6:
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 5:
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "  O   |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 4:
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "  O   |" << endl;
            cout << "  |   |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 3:
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "  O   |" << endl;
            cout << " /|   |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 2:
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "  O   |" << endl;
            cout << " /|\\  |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 1:
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "  O   |" << endl;
            cout << " /|\\  |" << endl;
            cout << " /    |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 0:
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "  O   |" << endl;
            cout << " /|\\  |" << endl;
            cout << " / \\  |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
    }
}

string DisplayCorrect(string ref, string hidden, char show) {
    for (int i = 0; i < ref.length(); i++) {
        if (show == ref[i]) {
            hidden[i] = ref[i];
        }
        else if (hidden[i] != '_'){
            hidden[i] = '_';
        }
    }
    return hidden;
}

char GetUsin() {
    char usin;
    while (true)
    {
        cout << "Guess a character: "; // prompt user for a character
        char temp;
        cin >> temp;
        usin = tolower(temp);
        if (usin >= 'a' && usin <= 'z') { // check if user enter a character
            break;
        }
    }
    system("cls");
    return usin;
}

bool CheckUsin(string ref, char letter) {
    for (int i = 0; i < ref.size(); i++) {
        if (letter == ref[i]) {
            return true;
        }
    }
    return false;
}