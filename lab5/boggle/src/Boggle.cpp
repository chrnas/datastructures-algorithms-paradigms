// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "set"
#include "unordered_set"

using namespace std;

static const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
                                          "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
                                          "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
                                          "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
                                          "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
                                 };

int Boggle::getPlayerScore(){
    return playerScore;
}

int Boggle::getComputerScore(){
    return computerScore;
}

bool Boggle::makeBoard(const string &userInput){
    playerScore = 0;
    computerScore = 0;
    currentLetterBoard = Grid<char>(4,4);
    if((int)userInput.length() != NUM_CUBES){
        return false;
    }
    else{
        int totalCount = 0;
        for(int x = 0; x < 4; x++){
            for(int y = 0; y < 4; y++){
                currentLetterBoard[x][y] = std::toupper(userInput[totalCount]);
                ++totalCount;
            }
        }
        return true;
    }
}

void Boggle::makeRandomBoard(){
    playerScore = 0;
    computerScore = 0;
    currentLetterBoard = Grid<char>(4,4);
    string shuffledCubes[NUM_CUBES];
    for(int i = 0; i < NUM_CUBES; i++){
        shuffledCubes[i] = CUBES[i];
    }
    shuffle(shuffledCubes, NUM_CUBES);
    for(int i = 0; i < 4; i++){
        for(int y = 0; y < 4; y++){
            char cube[CUBE_SIDES];
            for(int x = 0; x < 6; x++){
                cube[x] = shuffledCubes[i+y][x];
            }
            shuffle(cube, 6);
            currentLetterBoard.set(i, y, cube[0]);
        }
    }
}

Grid<char> Boggle::getBoard(){
    return currentLetterBoard;
}

bool Boggle::searchWordFromStartPos(const string &word, int letterIndex, int posx, int posy){
    //Base case
    if(currentLetterBoard.get(posx, posy) == word[(int)word.length()-1] && letterIndex == (int)word.length()){
        return true;
    }

    bool wordFound = false;
    if(LEXICON.containsPrefix(word)){
        for(int x = -1; x < 2; x++){
            for(int y = -1; y < 2; y++){
                int cubePosx = posx + x;
                int cubePosy = posy + y;
                bool notSelf = !(x == 0 && y == 0);
                bool inBounds = !(cubePosx < 0 || 0 > cubePosy) && !(cubePosx > 3 || cubePosy > 3);
                if(notSelf && inBounds && (currentLetterBoard.get(cubePosx, cubePosy) == word[letterIndex])){
                    //Recursion
                    wordFound = wordFound || searchWordFromStartPos(word, letterIndex+1, cubePosx, cubePosy);
                }
            }
        }

        return wordFound;
    }
    else{
        return false;
    }
}

bool Boggle::searchWord(const string & word){
    if(LEXICON.contains(word) && (int)word.size() > 3){
        for(int x = 0 ; x < 4; x++){
            for(int y = 0; y < 4; y++){
                if(searchWordFromStartPos(word, 0, x, y)){
                    playerScore += (word.size()-3);
                    return true;
                }
            }
        }
    }
    return false;
}

set<string> Boggle::dataSearchAllWordsHelp(Grid<char> letterBoard,Grid<bool> visitedBoard, int posX, int posY, string currentWord, set<string> words){
    //Add current letter to the potential word or prefix
    currentWord = currentWord + letterBoard[posX][posY];

    //If the word now is a real word and is above the size of four, add it to the word list
    if(currentWord.size() >= 4 && LEXICON.contains(currentWord)){
        words.insert(currentWord);
    }
    //Recursivly check all 8 squares around the cube to form words
    if(LEXICON.containsPrefix(currentWord)){
        for (int x = posX - 1; x <= posX + 1; x++){
            for (int y = posY - 1; y <= posY + 1; y++){
                if (x >= 0 && y >= 0 && x < 4 && y < 4){
                    if(!visitedBoard[x][y]){
                        visitedBoard[x][y] = true;
                        words = dataSearchAllWordsHelp(letterBoard, visitedBoard, x, y, currentWord, words);
                    }
                }
            }
        }
    }
    //Base-case, return all the found words, if any
    return words;
}

set<string> Boggle::dataSearchAllWords(set<string> playerWords){
    set<string> words = {};
    string currentWord = "";
    Grid<bool> visitedBoard = Grid<bool>(4,4);
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            visitedBoard[x][y] = false;
        }
    }
    //Recusivly check all tiles as starting positions
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            visitedBoard[x][y] = true;
            set<string> currentWords;
            set<string> newWords;
            currentWords = dataSearchAllWordsHelp(currentLetterBoard,visitedBoard,x,y,currentWord,newWords);
            for(const string &word: currentWords) {
                words.insert(word);
            }
            visitedBoard[x][y] = false;
        }
    }
    // Sort list and generate score
    computerScore = 0;
    set<string> finalComputerWords;
    for(string word: words){
        if(!playerWords.count(word)){
            computerScore += (word.size()-3);
            finalComputerWords.insert(word);
        }
    }
    return finalComputerWords;
}


// TODO: implement the members you declared in Boggle.h
