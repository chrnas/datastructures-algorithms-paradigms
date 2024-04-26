// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "grid.h"
#include "set"
#include "lexicon.h"
// TODO: include any other header files you need

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    const Lexicon LEXICON = Lexicon(DICTIONARY_FILE);
    //Active Functions
    /**
     * Uses recurive backtracking to find all possible real formable words according to LEXICON in the boggle board and returns them as a set.
     * Calls dataSearchWordsHelp on every boggle letter position;
     *
     * Sorts out the words that the player already has guessed from the computer generated words and composes a score from this sorted list.
     *
     * @return set<string> of words containing all possible real formable words according to LEXICON of the boggle board that the player has not guessed.
     */
    set<string> dataSearchAllWords(set<string> playerWords);



    /**
     * Creates a boggle board representing the Letters of userInput and returns true if successful.
     *
     * @param userInput String that represents the new board, should be 16;
     * @return true if successful, false if failed.
     */
    bool makeBoard(const string &userInput);

    /**
     * Creates a random board as the current boggle board;
     */
    void makeRandomBoard();

    /**
     * Checks if string word is a formable real words accourding to LEXICON,
     * calls searchWordFromStartPos() at every boggle board position.
     *
     * @param word A string representing the word that is searched for.
     * @return A boolean which is true if a formable real words accourding to LEXICON is found in any starting position otherwise false.
     */
    bool searchWord(const string & word);

    /**
     * Getter for getting the playerScore from a boggle board.
     *
     * @return An int representing the playerScore of the boggle board.
     */
    int getPlayerScore();

    /**
     * Getter for getting the computerScore from a boggle board.
     *
     * @return An int representing the computerScore of the boggle board.
     */
    int getComputerScore();

    Grid<char> getBoard();



private:
    /**
     * Uses recurive backtracking to find all possible real formable words according to LEXICON
     * in boggle board with starting letter at (posX,posY)
     *
     * @param letterBoard A Grid of chars representing the boggle board.
     * @param visitedBoard A Grid of booleans representing every boggle board letters position been visited or not.
     * @param posX An int representing X-coordinate for currentWords first letter.
     * @param posY An int representing Y-coordinate for currentWords first letter.
     * @param currentWord A string representing the current built word.
     * @param words A set of strings representing all found real formable words accourding to LEXICON.
     * @return A set of string containing all found real formable words accourding to LEXICON that have starting Letter att position (posX,posY)
     */
    set<string> dataSearchAllWordsHelp(Grid<char> letterBoard,Grid<bool> visitedBoard, int posX, int posY, string currentWord,set<string> words);

    /**
     * Recursivly checks if string word is a formable real words accourding to LEXICON
     * in the boggle board which starting Letter is at position (posX,posY).
     *
     * @param word A string representing the word that is searched for.
     * @param letterIndex An´
     * @param posx X-cordinate of the position for the first Letter of Word.
     * @param posy Y-cordinate of the position for the first Letter of Word.
     * @return Returns a boolean which is true if a formable real words accourding to LEXICON is found with starting position (posX,posY) otherwise false.
     */
    bool searchWordFromStartPos(const string &word, int letterIndex, int posx, int posy);


    // TODO: decide the private member variables/functions and declare them
    Grid<char> currentLetterBoard;
    int computerScore;
    int playerScore;
    //What to write here??
};

#endif
