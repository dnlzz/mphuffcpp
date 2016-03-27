#include "huffman.h"
#include "heapPQueue.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <istream>


const int NUM_CHAR = 256;
int charCount[NUM_CHAR];
string code[NUM_CHAR] = {};
Node *root;

//int[] freq;
//int[] charLocs;


Huffman::Huffman()
{
	cout << "Huff" << endl;
}

void Huffman::encode(char* f, ofstream& o) {
	bytes = readAllBytes(f);
	getFreq();
	printVector();
	root = buildMinHeap();
	
	buildCode(code, root, "");
	writeTree(root);
	string outStr = generateEncodedString();
	//string convertedString = convert(outStr);
	string convertedStr = outStr;
	string fName(f);
	fName += ".huf";
	writeToFile(fName, o, convertedStr);

}


vector<char> Huffman::readAllBytes(char const* fn)
{
	ifstream ifs(fn, ios::binary | ios::ate);
	ifstream::pos_type pos = ifs.tellg();

	vector<char>  result(pos);

	ifs.seekg(0, ios::beg);
	ifs.read(&result[0], pos);
	cout << "post read:" << endl;
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

void Huffman::writeTree(Node* x) {
	if (x->isLeaf()) {
		//System.out.println(x.data);
		return;
	}
	writeTree(x->left);
	writeTree(x->right);
}

void Huffman::buildCode(string st[], Node* x, string s) {
	if (!x->isLeaf()) {
		buildCode(st, x->left, s.append("0"));
		buildCode(st, x->right, s.append("1"));
	}
	else {
		st[x->data] = s;

	}
}

string convert(string bits) {
	string out(bits.size() / 8, 0);
	for (int i = 0; i < bits.size(); i++) {
		if (bits[i] == '1') {
			out[i / 8] |= 1 << (7 - (i % 8));
		}
	}
	return out;
}

string Huffman::generateEncodedString() {

	double count = 0;
	output = "";

	cout << "Original Count: " << (double)(bytes.size() * 8) << endl;

	for (int i = 0; i < bytes.size(); i++) {
		if (bytes[i] > 0) {
			string outCode = code[bytes[i]];
			output += outCode;
			count += outCode.length();
		}
	}

	double savings = ((count / (double)(bytes.size() * 8)) * 100);

	cout << "Compressed Count: " <<  count << endl;
	cout << "Savings: " << savings << " %" << endl;

	return output;

}

void Huffman::writeToFile(string f, ofstream& o, string s) {

	cout << "Writing to: " << f << endl;

	for (int i = 0; i < s.length(); i++)
	{
		o << s[i];
	}

	cout << "Sucessfully written!" << endl;
}