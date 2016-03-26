#include "huffman.h"
#include "heapPQueue.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>


const int NUM_CHAR = 256;
int charCount[NUM_CHAR];
//char *code[NUM_CHAR];
Node *root;
//int[] freq;
//int[] charLocs;


Huffman::Huffman()
{
	cout << "Huff" << endl;
}

void Huffman::encode(char* f) {
	bytes = readAllBytes(f);
	getFreq();
	printVector();
	root = buildMinHeap();

}


vector<char> Huffman::readAllBytes(char const* fn)
{
	ifstream ifs(fn, ios::binary | ios::ate);
	ifstream::pos_type pos = ifs.tellg();

	vector<char>  result(pos);

	ifs.seekg(0, ios::beg);
	ifs.read(&result[0], pos);

	return result;
}

void Huffman::printVector() {
	for (int i = 0; i < bytes.size(); i++) {
		cout << bytes[i] << endl;
	}

	for (int i = 0; i < NUM_CHAR; i++) {
		if (charCount[i] > 0)
			cout << i << "\t" << charCount[i] << endl;
	}

}

void Huffman::getFreq() {
	for (int i = 0; i < NUM_CHAR; ++i)
		charCount[i] = 0;

	cout << bytes[0] << endl;

	int k = 0;
	for (int j = 0; j < bytes.size(); j++) {
		if (bytes[k] >= 0 && bytes[k] < NUM_CHAR)
		{
			charCount[bytes[j]]++;
			k++;
		}
	}
}

Node* Huffman::buildMinHeap() {

	heapPQueue *pq = new heapPQueue();

	for (int i = 0; i < NUM_CHAR; i++)
		if (charCount[i] > 0) {
			pq->add(new Node(i, charCount[i], NULL, NULL));
	}

	// merge two smallest trees
	while (pq->size() > 1) {
		Node *left = pq->remove();
		Node *right = pq->remove();
		Node *parent = new Node('\0', left->freq + right->freq, left, right);
		pq->add(parent);
	}
	return pq->remove();
}