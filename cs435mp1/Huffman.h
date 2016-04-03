#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "Node.h"
#include <fstream>
#include <string>
#include "heapPQueue.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <istream>
#include "bitIO.h"

using namespace std;

class Huffman
{
public:
	Huffman();
	void encode(char*);
	vector<char> readAllBytes(char const*);
	void printVector();
	void getFreq(char const*);
	Node* buildMinHeap();
	string convert(string);
	void writeTree(Node*);
	void buildCode(string[], Node*, string);
	string generateEncodedString();
	vector<int> strToVec(string);
	void generateHeader();

	void writeHeader(obstream&, Node*, string);
	void preOrder(Node*);

	void decode(char*);
	string readHeader(char*);
	void readContents(char*);
	void traverse();
	vector<char> bytes;
	string output;

};

#endif