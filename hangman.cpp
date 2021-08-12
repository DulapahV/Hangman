// Written by Dulapah Vibulsanti (64011388)
// Hangman Project
// See README.txt for more information.

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>
#include <time.h>

using namespace std;

// function prototype
fstream &ReadLine(fstream& file, unsigned int num); // read a specific line in word.txt and return the text in that line
int GetRandInt();
string GetWord(unsigned int num); // get a random word from word.txt
int HangMan(int num); // print out a Hangman
string DisplayCorrect(string ref, string hidden, char show); // print out "_" and/or corrected guess
char GetUsin(); // get user input
bool CheckUsin(string ref, char letter); // check whether user's guess is correct


// main driver
int main() {
    string word = GetWord(GetRandInt()); // Get a word
    int wordLength = word.length(); // Get word length

    vector<string> guess; // Create a "_" to show user
    for (int i = 0; i < wordLength; i++) {
        guess.push_back("_");
    }

    cout << "Choosen word is " << word << endl; // DEBUG
    
    int life = 10; // player's life
    HangMan(life);   
    cout << "Remaining Life: " << life << endl << endl;

    for (int i = 0; i < wordLength; i++) { // print "_"
        cout << guess[i] << " ";
    }
    cout << endl << endl;
    //cout << string(2, '\n'); // DEBUG

    while (life > 0) {
        if (CheckUsin(word, GetUsin())) { // check if correct
            cout << "YES" << endl;
            HangMan(life);
            cout << "Remaining Life: " << life << endl << endl;

            for (int i = 0; i < wordLength; i++) { // print "_"
                cout << guess[i] << " ";
            }
            cout << endl << endl;
        }
        else {
            life--;
            HangMan(life);
            cout << "Remaining Life: " << life << endl << endl;

            for (int i = 0; i < wordLength; i++) { // print "_"
                cout << guess[i] << " ";
            }
            cout << endl << endl;
        }
    }
    cout << "You loose :(" << endl;
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

// hangman ASCII art provided by https://gist.github.com/chrishorton/8510732aa9a80a03c829b09f12e20d9c
int HangMan(int num) {
    switch (num) {
        case 10:
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "       " << endl;
            cout << "=========" << endl;
            break;
        case 9:
            cout << "       " << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 8:
            cout << "  +---+" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 7:
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 6:
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "  O   |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 5:
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "  O   |" << endl;
            cout << "  |   |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 4:
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "  O   |" << endl;
            cout << " /|   |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 3:
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "  O   |" << endl;
            cout << " /|\\  |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 2:
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "  O   |" << endl;
            cout << " /|\\  |" << endl;
            cout << " /    |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
        case 1:
            cout << "  +---+" << endl;
            cout << "  |   |" << endl;
            cout << "  O   |" << endl;
            cout << " /|\\  |" << endl;
            cout << " / \\  |" << endl;
            cout << "      |" << endl;
            cout << "=========" << endl;
            break;
    }
    return 0;
}

string DisplayCorrect(string ref, string hidden, char show) {
    
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
    cout << endl << endl;
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