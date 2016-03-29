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
	void getFreq();
	Node* buildMinHeap();
	string convert(string);
	void writeTree(Node*);
	void buildCode(string[], Node*, string);
	string generateEncodedString();
	vector<int> strToVec(string);
	string generateHeader();
	void writeToFile(string, obstream&, string);
	void preOrder(Node*, vector<int>&);

	void decode(char*);
	vector<int> readFile(char*);
	vector<char> bytes;
	string output;
	
//private:
	//String encodeFile();
	//byte[] convertToBytes()
	//Node* buildMinHeap();
	//void buildCode(String[] st, Node x, String s);
	//void writeTree(Node* x);

};

#endif