/**
 * created by chrna581, Christoffer Näs and miklu523, Mikael Lundgren.
 * The program reads in two words from terminal and a dictionary from a file.
 * Then the program creates wordchains out of the words from the dictionary beetween the read in words
 * and prints the shortest wordchain in the terminal.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

queue<string> neighbour(const string &word);

unordered_set<string> getNeighbour(const string &word, const unordered_set<string> &hashDict);

stack<string> wordChain(const string &word1, const string &word2);

/**
 * Takes two words through terminal
 * and prints the shortest possible wordchain
 * choosing words from dictionary.txt
 * from first word to last in terminal.
 *
 * @return 0 to quit the function.
 */
int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;
    cout << "Please type two words: ";
    string word1 = "";
    string word2 = "";
    cin >> word1 >> word2;
    stack<string> chain = wordChain(word1, word2);
    int chainSize = (int)chain.size();
    while(!chain.empty())
    {
        cout << chain.top() << " ";
        chain.pop();
    }
    cout << endl;
    return 0;
}

/**
 * Checks shortest possible word chain beetween word1 and word2
 * choosen from the words inside dictionary.txt
 *
 * @param word1 first string read from terminal, determines end of word chain
 * @param word2 second string read from terminal, determines first of word chain
 * @return a stack containing the a wordchain of strings
 */
stack<string> wordChain(const string &word1, const string &word2)
{
    fstream dictFile;
    dictFile.open("dictionary.txt");
    string line = "";
    unordered_set<string> hashDict;
    while (getline(dictFile, line))
    {
        hashDict.insert(line);
    }
    queue<stack<string>> alternatives;
    unordered_set<string> usedNeighbour;
    stack<string> stack1;
    stack1.push(word1);
    alternatives.push(stack1);
    usedNeighbour.insert(word1);

    while (!alternatives.empty())
    {
        stack<string> partialChain(alternatives.front());
        alternatives.pop();
        if(partialChain.top() == word2)
        {
            return partialChain;
        }
        else
        {
            unordered_set<string> neighbour = getNeighbour(partialChain.top(), hashDict);
            stack<string> newPartialChain(partialChain);
            for(auto& it:neighbour)
            {
                if (!usedNeighbour.count(it))
                {
                     usedNeighbour.insert(it);
                     newPartialChain.push(it);
                     alternatives.push(newPartialChain);
                     newPartialChain = partialChain;
                }
            }
        }
    }
    stack<string> stack;
    stack.push("empty");
    return stack;
}

/**
 * Gets neighbours in hashDict to word and returns them
 *
 * @param a string word, which the function gets all nieghbours to
 * @param an unordered_set hashDict containing all neighbours to the string word
 * @return an unordered_set containing all neighbours as strings
 */
unordered_set<string> getNeighbour(const string &word, const unordered_set<string> &hashDict)
{
    unordered_set<string> neighbour;
    string maybeNeighbour = word;
    for(int i = 0; i < (int)word.length(); i++)
    {
        maybeNeighbour = word;
        for(auto& z:ALPHABET)
        {
            maybeNeighbour[i] = z;
            if(hashDict.count(maybeNeighbour) && maybeNeighbour != word)
            {
                neighbour.insert(maybeNeighbour);
            }
        }
    }
    return neighbour;
}
