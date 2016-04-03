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

	string act = action;

	Huffman h;

	if (act == "henc")
	{
		h.encode(fn);
	}

	else if (act == "hdec")
	{
		h.decode(fn);
	}

	return 0;
}

