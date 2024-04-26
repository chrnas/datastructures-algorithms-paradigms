/* Detta är implementationen av encoding.h. Funktionerna i denna fil kan huffmanendkoda och -dekoda godtyckgliga filer.
 * */

#include "encoding.h"
#include "HuffmanNode.h"
#include <vector>
#include <queue>


map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    char c;
    while(input.get(c)){//Put all the character in the map, and add to their frequences
        freqTable[(int)c] += 1;
    }
    freqTable[PSEUDO_EOF] += 1; // We have reached end
    input.clear();
    input.seekg(0, ios::beg); // Reset the in-stream
    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    priority_queue<HuffmanNode> pQueue;

    for(std::pair<int, int> pair:freqTable)
    {// Create a node for each element in the frequency map and put it in the priority queue
        HuffmanNode node = HuffmanNode(pair.first, pair.second, nullptr, nullptr);
        pQueue.emplace(node);
    }

    while((int)pQueue.size() > 1){// Take out the nodes with the lowest frequencies and link them to a new node without a character
        HuffmanNode* node1 = new  HuffmanNode(pQueue.top());
        pQueue.pop();
        HuffmanNode* node2 = new HuffmanNode(pQueue.top());
        pQueue.pop();
        HuffmanNode newNode = HuffmanNode(NOT_A_CHAR, node1->count + node2->count, node1, node2);
        pQueue.push(newNode);
    }
    HuffmanNode* rootNode = new HuffmanNode(pQueue.top()); // Assign a pointer to the root node and return it
    return rootNode;
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;

    if(encodingTree == nullptr){// base case, return an empty map
        return encodingMap;
    }

    std::pair<int, string> current(encodingTree->character, "");
    encodingMap[current.first] = current.second; // Add the current node to the encoding map
    map<int, string> leftTree = buildEncodingMap(encodingTree->zero); // Recusive call the the left side of the huffman tree
    map<int, string> rightTree = buildEncodingMap(encodingTree->one); // Recusive call the the right side of the huffman tree
    for(auto it = leftTree.begin(); it != leftTree.end(); it++){
        string zero = "0";
        it->second = zero.append(it->second);
    }
    for(auto it = rightTree.begin(); it != rightTree.end(); it++){
        string one = "1";
        it->second = one.append(it->second);
    }
    encodingMap.insert(leftTree.begin(), leftTree.end());
    encodingMap.insert(rightTree.begin(), rightTree.end());
    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    char letter;
    while(input.get(letter)){
        string binCode = encodingMap.at(letter);
        for(char bit:binCode){
            output.writeBit((bit == '1') ? 1 : 0);
        }
    }
    for(char bit:encodingMap.at(PSEUDO_EOF)){
        output.writeBit((bit == '1') ? 1 : 0);
    }
    input.clear();
    input.seekg(0, ios::beg);

}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    string binCode;
    int bit;
    bit = input.readBit();
    HuffmanNode* currentNode = encodingTree;
    while(bit != -1){
        if(bit == 1){
            currentNode = currentNode->one;
        }
        else{
            currentNode = currentNode->zero;
        }
        if(currentNode->isLeaf()){
            char nodeChar = (char)currentNode->character;
            output.put(nodeChar);
            currentNode = encodingTree;
        }
        bit = input.readBit();
    }
    input.clear();
    input.seekg(0, ios::beg);
}

void compress(istream& input, obitstream& output) {
    map<int, int> freqTable = buildFrequencyTable(input);
    HuffmanNode* tree = buildEncodingTree(freqTable);
    map<int, string> encodingMap = buildEncodingMap(tree);
    output.put('{');
    for(auto it = freqTable.begin(); it != freqTable.end(); it++){
        string first = std::to_string(it->first);
        string second = std::to_string(it->second);
        for(char index: first){
            output.put(index);
        }
        output.put(':');
        for(char index: second){
            output.put(index);
        }
        auto ifEndIt = it;
        ifEndIt++;
        if(ifEndIt != freqTable.end()){
            output.put(',');
            output.put(' ');
        }
    }
    output.put('}');
    input.clear();
    input.seekg(0, ios::beg);
    encodeData(input, encodingMap,output);
    freeTree(tree);
}

void decompress(ibitstream& input, ostream& output) {
    string charString;
    std::pair<int, int> freqPair;
    map<int, int> freqTable;
    char letter;
    input.get(letter);
    bool freqTreeDone = false;
    while(!freqTreeDone){
        input.get(letter);
        switch (letter) {
        case '}':
            freqPair.second = std::stoi(charString);
            freqTable[freqPair.first] = freqPair.second;
            charString.clear();
            freqTreeDone = true;
            break;
        case ':':
            freqPair.first = std::stoi(charString);
            charString.clear();
            break;
        case ',':
            freqPair.second = std::stoi(charString);
            freqTable[freqPair.first] = freqPair.second;
            charString.clear();
            break;
        case ' ':
            break;
        default:
            charString.push_back(letter);
            break;
        }
    }
    HuffmanNode* tree = buildEncodingTree(freqTable);
    decodeData(input, tree, output);
    input.clear();
    input.seekg(0, ios::beg);
    freeTree(tree);
}


void freeTree(HuffmanNode* node) {
    if(node != nullptr)
    {
        freeTree(node->zero);
        freeTree(node->one);
        delete node;
    }
}
