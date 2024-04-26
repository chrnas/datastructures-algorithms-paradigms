// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
// TODO: include any other header files you need

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)
    Grid<char> board;
    string prompt = "Do you want to assign a board manually? press y/n";
    if(yesOrNo(prompt)){
        bool okBoard = false;
        while(!okBoard)
        {
            cout << "Please give me 16 letters in a row:" << endl;
            string manualBoard;
            getline(cin, manualBoard);
            okBoard = boggle.makeBoard(manualBoard);
            if(!okBoard){
                cout << "not 16 letters" << endl;
            }
        }
    }
    else{
        boggle.makeRandomBoard();
    }
    set<string> playerWords;
    int a = 0;
    bool running = true;
    while(running){
        clearConsole();
        for(int i = 0; i < 4; i++){
            cout<<endl;
            for(int j = 0; j < 4; j++){
                char letter = boggle.getBoard()[i][j];
                cout << letter;
            }
        }
        cout <<endl<< "It's your turn" << endl;
        a = 0;
        cout << "Your words (" << playerWords.size() << "): {";
        for(string word : playerWords){
            a++;
            cout << '"' << word << '"';
            if(!(a == (int) playerWords.size())){
                cout << ",";
            }
        }
        cout << "}" << endl;
        cout << "Your Score: " << boggle.getPlayerScore() << endl;
        string guessedWord;
        cout << "Type a word(or press ENTER to end your turn)" << endl;
        getline(cin,guessedWord);
        guessedWord = trim(toUpperCase(guessedWord));
        if(guessedWord == ""){
            running = false;
        }
        if(!playerWords.count(guessedWord) && boggle.searchWord(guessedWord)){
            cout << "You found a new word!" << '"' << guessedWord << '"' << endl;
            playerWords.insert(guessedWord);
        }
    }

    cout << "It's my turn!" << endl;
    set<string> computerWords = boggle.dataSearchAllWords(playerWords);

    cout << "My words (" << computerWords.size() << "): ";
    cout <<  '{' << '"';
    a = 0;
    for(string word:computerWords){
        a++;
        cout << word << '"';
        if(!(a == (int) computerWords.size())){
            cout << ", ";
        }
    }
    cout << "}" << endl;
    cout << "My Score: " << boggle.getComputerScore() << endl;
    if(boggle.getComputerScore() > boggle.getPlayerScore()){
        cout << "ha ha ha, i destroyed you. Better luck next time, puny human!" << endl;
    }
    else{
        cout << "You beat me this time puny human, but ill get you in the next!" << endl;
    }
}



/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
