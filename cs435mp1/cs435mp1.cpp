// cs435mp1.cpp : Defines the entry point for the console application.
//

#include "heapPQueue.h"
#include "Node.h"
#include <iostream>
#include "Huffman.h"
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
	char *action = argv[1];
	char *fn = argv[2];

	string fStr(fn);
	fStr += ".huf";
	string fn(fn);

	ofstream oFile(fStr, ios::binary);
	ifstream iFile(fn, ios::binary);

	Huffman h;

	//h.encode(fn, oFile);
	h.decode(fn, iFile);

	oFile.close();
	iFile.close();

	return 0;
}

