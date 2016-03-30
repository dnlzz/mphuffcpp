// cs435mp1.cpp : Defines the entry point for the console application.
//

#include "heapPQueue.h"
#include "Node.h"
#include <iostream>
#include "Huffman.h"
#include <fstream>
#include <string>

using namespace std;

class MyClass
{
public:
	MyClass();
	~MyClass();
	void read();
	void write();

private:

};

MyClass::MyClass()
{
	cout << "testerr..." << endl;
}

MyClass::~MyClass()
{
}

void MyClass::read() {
	char* fn = "C:\\Users\\Tony\\Desktop\\test.txt.huf";
	vector<int> bits;
	ifstream ifs(fn, ios::binary);
	ibstream ib(ifs);
	int counter = 0;
	while (ib.readBit() != EOF)
	{
		bits.push_back(ib.readBit());
	}

	cout << bits.size() << endl;
	for (int i = 0; i < bits.size(); i++)
	{
		cout << bits[i];

		if (i%8==0)
		{
			cout << endl;
		}
	}
	
}


int main(int argc, char* argv[])
{
	char *action = argv[1];
	char *fn = argv[2];

	//MyClass m;
	//m.read();

	//ofstream oFile(fn, ios::binary);
	//ifstream iFile(fname, ios::binary);

	Huffman h;

	h.encode(fn);
	//h.decode(fn);

	//oFile.close();
	//iFile.close();

	return 0;
}

