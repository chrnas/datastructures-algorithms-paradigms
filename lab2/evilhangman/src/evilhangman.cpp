/**
 * created by chrna581, Christoffer Näs and miklu523, Mikael Lundgren.
 * The project relizes the game Hangman in Terminal but changes some of the rules to create the Evil Hangman.
 * The game is setup by reading in a couple of ints and a string through terminal. The player can guess letters through terminal.
 * The program compares structures of the possible words left that contain the guessed letter and choses the collection with the most words.
 * When only one word is left and all the letters are guessed the player has won.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

vector<string> guess(const vector<string> &currentWordList,const char guessedLetter);

bool checkCorrectWord(const unordered_set<char> &guessedLetters,const string &word);

string buildCurrentWord(const string &word,const unordered_set<char> &guessedLetters);

string getStructure(const string &word, const char guessedLetter);

bool isNumber(string& str);

bool isThereAWordWithLength(const int lengthWord, const vector<string>& wordlist);

/**
 * The player can play a game of hanging man in console,
 * however the computer will cheat against the player.
 * The computer saves all possible words that are possible with guessed letters.
 * The player will only win when there are only one possible word.
 *
 * @return returns 0 when the game has ended to quit the program.
 */
int main() {

    cout << "Welcome to Hangman." << endl;

    vector<string> currentWordList;
    unordered_set<char> guessedLetters;
    vector<string> origWordList;

    fstream dictFile;
    dictFile.open("dictionary.txt");
    string line = "";

    while (getline(dictFile, line))
    {
        origWordList.push_back(line);
    }

    int lengthWord;
    string lengthWordStr;
    bool correctLength = false;
    while(!correctLength){
        cout << "Choose a word length: ";
        cin >> lengthWordStr;
        if(isNumber(lengthWordStr)){//Komplettering 2
            lengthWord = stoi(lengthWordStr);
            correctLength = isThereAWordWithLength(lengthWord, origWordList);
        }
    }

    int numberOfGuesses;
    string numberOfGuessesStr;
    string currentWord;
    bool noGuesses = false;
    while(!noGuesses){
        cout << "Choose Number of guesses: ";
        cin >> numberOfGuessesStr;
        if(isNumber(numberOfGuessesStr)){
            numberOfGuesses = stoi(numberOfGuessesStr);
            noGuesses = numberOfGuesses>0;
        }
    }

    cout << "Do you want to see remaining words? 1/yes, 0/no: ";
    bool showRemainingWords;
    cin >> showRemainingWords;

    for(int i = 0; i < (int)origWordList.size(); i++){
        if(lengthWord == (int)origWordList[i].length()){
            currentWordList.push_back(origWordList[i]);
        }
    }
    while(numberOfGuesses > 0){
        cout << "Number of Guesses: " << numberOfGuesses << endl;
        if(showRemainingWords){
            cout << "Remaining possible words: " << currentWordList.size() << endl;
        }

        cout << "Guess a Letter: ";
        char guessedLetter;
        string guessedLetterStr;
        cin >> guessedLetterStr;
        if((int)guessedLetterStr.size() == 1 && guessedLetterStr.find(ALPHABET)){
            guessedLetter = guessedLetterStr[0];
            if(!guessedLetters.count(guessedLetter))
            {
                guessedLetters.insert(guessedLetter);

                currentWordList = guess(currentWordList, guessedLetter);
                currentWord = *currentWordList.begin();
                currentWord = buildCurrentWord(currentWord, guessedLetters);

                cout << "Current Version of the Word: " << currentWord << "\n" << endl;
                if(currentWordList.size() == 1 && checkCorrectWord(guessedLetters, *currentWordList.begin()))
                {
                    cout << "YOU WIN" << endl;
                    numberOfGuesses = 0;
                    break;
                }
                numberOfGuesses --;
            }
        }
    }

    return 0;
}

/**
 * Makes a guess
 *
 * @param currentWordList a list containing all current possible words
 * @param guessedLetter a char representing the guessed letter by the player in console
 * @return newWordList a list with all new possible words taken account of the new guessed letter.
 */
vector<string> guess(const vector<string> &currentWordList,const char guessedLetter){
    unordered_map<string, vector<string>> wordLists;
    vector<string> newWordList;
    for(auto currentWord:currentWordList){
        string structure = getStructure(currentWord, guessedLetter);
        wordLists[structure].push_back(currentWord);
    }
    for(auto it:wordLists){
        if(it.second.size() > newWordList.size()){
            newWordList = it.second;
        }
    }
    return newWordList;
}

/**
 * Checks if there is a word with the stated lenght in a vector of strings.
 *
 * @param lengthWord an integer lenght to be searched for
 * @param wordlist a vector of strings to be searched through
 * @return True if the is a word with the lenght of lenghtWord. False if there is not a word with lenght lenghtWord.
 */
bool isThereAWordWithLength(const int lengthWord, const vector<string>& wordlist){
    for(auto word:wordlist)
    {
        if((int)word.length() == lengthWord)
        {
            return true;
        }
    }
    return false;
}

/**
 * Creates a string that has replaced all letters expect the guessedLetter with "-" to get the structure of that word.
 *
 * @param word the word which the structure is created for.
 * @param guessedLetter the letter which the structure for the word is created.
 * @return a string structure containing the structure of the given word and char
 */
string getStructure(const string &word,const char guessedLetter){
    string structure = "-";
    string::size_type found = word.find_first_of(guessedLetter);
    while(found != string::npos){
        structure.push_back(found);
        found = word.find_first_of(guessedLetter, found+1);
    }
    return structure;
}

/**
 * checks if the guessedLetters containing the same letters as the given word.
 *
 * @param guessedLetters an unorderd_set containing all the letters that the player has guessed.
 * @param word a string representing the word that the guessedLetters are checked against.
 * @return returns a bool, true if the guessedLetters checks out against the word.
 */
bool checkCorrectWord(const unordered_set<char> &guessedLetters,const string &word){
    bool allLettersGuessed = false;
    for (int i = 0; i < (int)word.length(); i++){
        if(guessedLetters.count(word[i])){
            allLettersGuessed = true;
        }
        else{
            return false;
        }
    }
    return allLettersGuessed;

}

/**
 * Builds the current estimated word
 *
 * @param word a string representing a word that legoWord are built after
 * @param guessedLetters an unordered_set containing all current guessed letters
 * @return a string legoWord containing "-" for every non guessed letter.
 */
string buildCurrentWord(const string &word,const unordered_set<char> &guessedLetters)
{
    string legoWord = "";
    for (int i = 0; i < (int)word.size(); i++){
        if(guessedLetters.count(word[i])){
            legoWord.push_back(word[i]);
        }
        else{
            legoWord.push_back('-');
        }
    }
    return legoWord;
}

/**
 * Checks if a string is build up of only digits.
 * Returns true if only digits else false.
 */
bool isNumber(string& str)
{
    for (char &c : str) {
        if (std::isdigit(c) == 0)
            return false;
    }
    return true;
}
