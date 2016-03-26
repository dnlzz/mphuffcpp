// cs435mp1.cpp : Defines the entry point for the console application.
//

#include "heapPQueue.h"
#include "Node.h"
#include <iostream>
#include "Huffman.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	char *action = argv[1];
	char *fn = argv[2];

	Huffman h;

	cout << fn << endl;

	h.encode(fn);

	return 0;
}

