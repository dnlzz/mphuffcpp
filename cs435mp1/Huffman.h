#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "Node.h"
#include <vector>

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
	vector<char> bytes;
	
//private:
	//String encodeFile();
	//byte[] convertToBytes()
	//Node* buildMinHeap();
	//void buildCode(String[] st, Node x, String s);
	//void writeTree(Node* x);

};

#endif