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

	string fname(fn);

	//ofstream oFile(fn, ios::binary);
	//ifstream iFile(fname, ios::binary);

	Huffman h;

	h.encode(fn);
	//h.decode(fn);

	//oFile.close();
	//iFile.close();

	return 0;
}

