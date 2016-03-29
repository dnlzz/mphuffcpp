#include "Huffman.h"



const int NUM_CHAR = 256;
int charCount[NUM_CHAR];
string code[NUM_CHAR] = {};
vector<int> codes;
Node *root;

//int[] freq;
//int[] charLocs;


Huffman::Huffman()
{
	cout << "Let's work on getting that file compressed!" << endl;
}

void Huffman::encode(char* f) {
	bytes = readAllBytes(f);
	getFreq();
	printVector();
	root = buildMinHeap();
	buildCode(code, root, "");
	writeTree(root);
	string outStr = generateEncodedString();
	cout << "outStr: " << outStr << endl;
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
		//System.out.println(x.data);
		return;
	}
	writeTree(x->left);
	writeTree(x->right);
}

void Huffman::buildCode(string st[], Node* x, string s) {
	if (!x->isLeaf()) {
		buildCode(st, x->left, s.append("0 "));
		buildCode(st, x->right, s.append("1 "));
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

	cout << "Original Count: " << (double)bytes.size() << endl;

	for (int i = 0; i < bytes.size(); i++) {
		if (bytes[i] > 0) {
			string outCode = code[bytes[i]];
			output += outCode;
			count += outCode.length();
		}
	}

	double savings = ( (count/8) / (double)bytes.size() * 100);

	cout << "Compressed Count: " <<  (int)count/8 << endl;
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

	for (int i = 0; i < NUM_CHAR; i++)
	{
		//out = out + to_string(charCount[i]) + " ";
	}

	return out;
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

	for (int i = 0; i < bytes.size(); i++)
	{
		cout << bytes[i] << endl;
	}

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
	while (iFile)
	{
		ints.push_back(i.readBit());
	}

	cout << ints.size() << endl;

	for (int i = 0; i < ints.size(); i++)
	{
		cout << ints[i] << " ";
	}

	iFile.close();

	return ints;

}