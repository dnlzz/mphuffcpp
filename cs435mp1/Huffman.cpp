#include "Huffman.h"



const int NUM_CHAR = 256;
int charCount[NUM_CHAR];
string code[NUM_CHAR];
vector<int> codes;
vector<int> treeHeader;
string header;
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
	bytes = readAllBytes(f);
	getFreq(f);
	//printVector();
	root = buildMinHeap();
	buildCode(code, root, "");
	writeTree(root);
	string outStr = generateEncodedString();
	cout << "outStr: " << outStr << endl;
	codes = strToVec(outStr);
	
	string fName(f);
	fName += ".huf";

	cout << "Writingn to: " << fName << endl;
	ofstream oFile(fName, ios::binary);
	obstream o(oFile);

	string headerStr = generateHeader(o);
	treeHeader = strToVec(header);

	treeHeader.insert(treeHeader.end(), codes.begin(), codes.end());

	for (int j = 0; j < treeHeader.size(); j++)
	{
		cout << treeHeader[j];
	}

	cout << "\nWrite size " << treeHeader.size() << endl;

	o.writeBits(treeHeader);
	
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

void Huffman::getFreq(char const* fn) {
	/*for (int i = 0; i < NUM_CHAR; ++i) {
		charCount[i] = 0;
	}

	int k = 0;
	for (int j = 0; j < bytes.size(); j++) {
		if (bytes[k] >= 0 && bytes[k] < NUM_CHAR)
		{
			charCount[bytes[j]]++;
			k++;
		}
	}*/

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
		//cout << "Data: " << x->data << endl;
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


string Huffman::generateEncodedString() {

	double count = 0;
	output = "";

	cout << "Original Count: " << (double)fSize << endl;

	
	for (int i = 0; i < bytes.size(); i++) {
		if (bytes[i] > 0) {
			string outCode = code[bytes[i]];
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

string Huffman::generateHeader(obstream& o) {
	string out = "";
	Node* tmp = root;

	//preOrder(tmp);

	header = "";
	writeHeader(o, tmp, "");
	header = header + "-1";
	cout << "header: " << header << endl;

	cout << "\n\n\nPoreorder ree size? " << treeHeader.size() << endl;

	return out;
}

void Huffman::writeHeader(obstream& out, Node* r, string s) {
	if (!r->isLeaf()) {
		writeHeader(out, r->left, s + "0 ");
		writeHeader(out, r->right, s + "1 ");
	}
	else {
		s += r->data;
		s = s + " ";
		header += s;
	}

}


void Huffman::decode(char* f) {
	cout << f << endl;
	vector<int> ints = readFile(f);



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
	vector<int> bits;
	ifstream ifs(f, ios::binary);
	ibstream ib(ifs);
	int counter = 0;
	while (ib.readBit() != EOF)
	{
		bits.push_back(ib.readBit());
	}

	return bits;

}

