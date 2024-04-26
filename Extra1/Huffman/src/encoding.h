/*
 * TDDD86 Huffman Encoding
 * This file declares the functions that you will need to write in this
 * assignment for your Huffman Encoder in huffmanencoding.cpp.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 */

#ifndef _encoding_h
#define _encoding_h

#include <iostream>
#include <string>
#include <map>
#include "bitstream.h"
#include "HuffmanNode.h"
using namespace std;

/*
 * See huffmanencoding.cpp for documentation of these functions
 * (which you are supposed to write, based on the spec).
 */

/**
 * @brief Creates a map there each pair depicts a char and the frequency of that char in a text-file.
 * @param The opened istream of a file.
 * @return A map that describes the frequency of different char:s
 */
map<int, int> buildFrequencyTable(istream& input);

/**
 * @brief Creates a huffman-tree with huffmannodes. The nodes that have the most frequent characters are the highest leaves.
 * @param freqTable
 * @return
 */
HuffmanNode* buildEncodingTree(const map<int, int>& freqTable);

/**
 * @brief Creates an map that has a char in int form and a string of bits that describe the path to that char in a specific encoding tree
 * @param encodingTree
 * @return
 */
map<int, string> buildEncodingMap(HuffmanNode* encodingTree);

/**
 * @brief Reades character by character and writes the bit path to each character, resulting in huffman-encoded data.
 * @param input
 * @param encodingMap
 * @param output
 */
void encodeData(istream& input, const map<int, string>& encodingMap, obitstream& output);

/**
 * @brief Traverses a specific encoding map by reading encoded data bit by bit and writes the characters that are reached.
 * @param input
 * @param encodingTree
 * @param output
 */
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output);

/**
 * @brief Uses encodedData() and compresses a file, adding the file-specific frequencymap as a header.
 * @param input
 * @param output
 */
void compress(istream& input, obitstream& output);

/**
 * @brief Reads a huffman compressed file and decompresses it by creating a frequency map from the header and applying decodeData on the rest of the file.
 * @param input
 * @param output
 */
void decompress(ibitstream& input, ostream& output);

/**
 * @brief Deletes a huffman tree from the heap.
 * @param node
 */
void freeTree(HuffmanNode* node);

#endif
