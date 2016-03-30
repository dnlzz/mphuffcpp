#include "Huffman.h"



const int NUM_CHAR = 256;
int charCount[NUM_CHAR];
string code[NUM_CHAR];
vector<int> codes;
vector<int> treeHeader;
Node *root;
int fSize;
char * buffer;

//int[] freq;
//int[] charLocs;


Huffman::Huffman()
{
	cout << "Let's work on getting that file compressed!" << endl;
}

void Huffman::encode(char* f) {
	readAllBytes(f);
	
	//getFreq();
	printVector();
	root = buildMinHeap();
	buildCode(code, root, "");
	writeTree(root);
	string outStr = generateEncodedString();
	//cout << "outStr: " << outStr << endl;
	codes = strToVec(outStr);
	//string convertedStr = convert(outStr);
	string headerStr = generateHeader();
	//string convertedHeaderStr = convert(headerStr);

	string fName(f);
	fName += ".huf";
	
	cout << "Writingn to: " << fName << endl;

	ofstream oFile(fName, ios::binary);
	obstream o(oFile);

	o.writeBits(codes);
	oFile.close();

	int numOut = 0;
	for (int i = 0; i < NUM_CHAR; i++)
	{
		if (charCount[i] > 0) {
			numOut += (code[i].size() / 2) * charCount[i];
			cout << code[i] << " : " << i << " : " << code[i].size()/2 << endl;
		}
	}

	cout << "total decompress size: " << numOut << endl;

}


//vector<char> Huffman::readAllBytes(char const* fn)
void Huffman::readAllBytes(char const* fn)
{
	/*
	ifstream ifs(fn, ios::binary | ios::ate);
	ifstream::pos_type pos = ifs.tellg();

	vector<char>  result(pos);

	ifs.seekg(0, ios::beg);
	ifs.read(&result[0], pos);

	return result;
	*/

	FILE * pFile;
	long lSize;
	size_t result;

	pFile = fopen(fn, "rb");
	if (pFile == NULL) { fputs("File error", stderr); exit(1); }

	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	// allocate memory to contain the whole file:
	buffer = (char*)malloc(sizeof(char)*lSize);
	if (buffer == NULL) { fputs("Memory error", stderr); exit(2); }

	// copy the file into the buffer:
	result = fread(buffer, sizeof(char), lSize, pFile);
	if (result != lSize) { fputs("Reading error", stderr); exit(3); }

	/* the whole file is now loaded in the memory buffer. */

	rewind(pFile);
	

	int ch;
	while ((ch = fgetc(pFile)) != EOF) {
		++charCount[ch];
		fSize++;
	}

	// terminate
	fclose(pFile);

	/*for (int i = 0; i < NUM_CHAR; i++)
	{
		cout << charCount[i] << "  ";
	}*/

	cout << "\nFsize" << fSize << endl;


}

void Huffman::printVector() {
	
	cout << "bytes" << endl;
	
	for (int i = 0; i < bytes.size(); i++) {
		cout << bytes[i] << " ";
	}

	cout << "counts" << endl;

	for (int i = 0; i < NUM_CHAR; i++) {
		if (charCount[i] > 0)
			cout << i << "\t" << charCount[i] << endl;
	}

}

void Huffman::getFreq() {
	for (int i = 0; i < NUM_CHAR; ++i) {
		charCount[i] = 0;
	}

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

	for (int i = 0; i < NUM_CHAR; i++) {
		if (charCount[i] > 0) {
			pq->add(new Node(i, charCount[i], NULL, NULL));
		}
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
		cout << "Data: " << x->data << endl;
		return;
	}
	writeTree(x->left);
	writeTree(x->right);
}

void Huffman::buildCode(string st[], Node* x, string s) {
	if (!x->isLeaf() ) {
		buildCode(st, x->left, s + "0 ");
		buildCode(st, x->right, s + "1 ");
	}
	else {
		st[x->data] = s;
	}
}

string Huffman::convert(string bits) {
	string out(bits.size() / 8, 0);
	for (int i = 0; i < bits.size(); i++) {
		if (bits[i] == '1') {
			out[i / 8] |= 1 << (7 - (i % 8));
		}
	}

	cout << "out: " << out << endl;

	return out;
}

string Huffman::generateEncodedString() {

	double count = 0;
	output = "";

	cout << "Original Count: " << (double)fSize << endl;

	
	for (int i = 0; i < NUM_CHAR; i++) {
		if (charCount[i] > 0) {
			string outCode = code[buffer[i]];
			output += outCode;
			count += outCode.length();
		}
	}

	double savings = ( (count/8) / (double)fSize * 100);

	cout << "Compressed Count: " <<  (int)fSize/8 << endl;
	cout << "Savings: " << savings << " %" << endl;

	return output;

}

vector<int> Huffman::strToVec(string s)
{
	vector<int> inputs;
	istringstream in(s);
	copy(std::istream_iterator<int>(in), std::istream_iterator<int>(),
		std::back_inserter(inputs));
	return inputs;
}

string Huffman::generateHeader() {
	string out = "";
	Node* tmp = root;

	preOrder(tmp);

	cout << "\n\n\nPoreorder ree size?" << treeHeader.size() << endl;

	return out;
}

void Huffman::preOrder(Node* r) {
	
	if (r == NULL)
		return;

	if (r->data != '\0') {
		cout << r->data << " ";
	}
	

	preOrder(r->left);
	preOrder(r->right);
	
}

void Huffman::writeToFile(string f, obstream &o, string h) {

	//ofstream o(f.c_str(), ios::binary);
	
	cout << "Writing to: " << f << endl;

	//o.writeBits(codes);

	/*
	for (int j = 0; j < h.length(); j++)
	{
		o << h[j];
	}

	o << endl;

	for (int i = 0; i < s.length(); i++)
	{
		o << s[i];
	}
	*/
	cout << "Sucessfully written!" << endl;
}

void Huffman::decode(char* f) {
	cout << f << endl;
	vector<int>ints = readFile(f);



	//printVector();
	//root = buildMinHeap();
	//buildCode(code, root, "");
	//writeTree(root);

}

vector<int> Huffman::readFile(char* f) {
	/*
	ifstream ifs(f, ios::binary | ios::ate);
	ifstream::pos_type pos = ifs.tellg();

	vector<char>  result(pos);

	ifs.seekg(0, ios::beg);
	ifs.read(&result[0], pos);

	return result;
	*/

	string fName(f);
	fName += ".huf";

	ifstream iFile(fName, ios::binary);
	ibstream i(iFile);
	vector<int> ints;
	vector<int> byts;
	string bints = "";
	while (iFile)
	{
		ints.push_back(i.readBit());
	}

	cout << ints.size() << endl;

	for (int i = 0; i < ints.size(); i++)
	{

		if (i % 8 == 0)
		{
			cout << endl;
		}
	}

	iFile.close();

	return ints;

}
