#include "Huffman.h"

const int NUM_CHAR = 256;
int charCount[NUM_CHAR];
string code[NUM_CHAR];
vector<int> codes;
vector<int> treeHeader;
string header, contents, decodedStr, strToDecode;
Node *root;
int headerCount;
char * buffer;

Huffman::Huffman()
{
	cout << "Let's work on getting that file compressed!" << endl;
}

void Huffman::encode(char* f) {
	bytes = readAllBytes(f);
	getFreq(f);
	root = buildMinHeap();
	buildCode(code, root, "");
	writeTree(root);

	string outStr = generateEncodedString();
	//codes = strToVec(outStr);
	
	generateHeader();
	//treeHeader = strToVec(header);

	string fName(f);
	fName += ".huf";

	ofstream outfile;
	outfile.open(fName.c_str(), ios_base::out | ios_base::binary | ios_base::app);
	obstream o(outfile);
	
	outfile << headerCount << " ";
	outfile << header;
	outfile << outStr;

	outfile.close();

}


vector<char> Huffman::readAllBytes(char const* fn)
{

	ifstream ifs(fn, ios_base::binary | ios_base::ate);
	ifstream::pos_type pos = ifs.tellg();

	vector<char>  result(pos);

	ifs.seekg(0, ios_base::beg);
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

	FILE * pFile;
	long lSize;
	size_t result;

	pFile = fopen(fn, "rb");
	if (pFile == NULL) { fputs("File error", stderr); }

	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	// allocate memory to contain the whole file:
	buffer = (char*)(sizeof(char)*lSize);
	if (buffer == NULL) { fputs("Memory error", stderr); }

	// copy the file into the buffer:
	result = fread(buffer, sizeof(char), lSize, pFile);
	if (result != lSize) { fputs("Reading error", stderr); }

	/* the whole file is now loaded in the memory buffer. */

	rewind(pFile);


	int ch;
	while ((ch = fgetc(pFile)) != -1) {
		++charCount[ch];
	}

	// terminate
	fclose(pFile);

	/*for (int i = 0; i < NUM_CHAR; i++)
	{
	cout << charCount[i] << "  ";
	}*/

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
		return;
	}
	writeTree(x->left);
	writeTree(x->right);
}

void Huffman::buildCode(string st[], Node* x, string s) {
	if (!x->isLeaf() ) {
		buildCode(st, x->left, s + "0"); //add space after 0 for bit reading/writing
		buildCode(st, x->right, s + "1"); //add space after 1 for bit reading/writing
	}
	else {
		st[x->data] = s;
	}
}


string Huffman::generateEncodedString() {

	double count = 0;
	output = "";

	for (int i = 0; i < bytes.size(); i++) {
		if (bytes[i] > 0) {
			string outCode = code[bytes[i]];
			output += outCode;
			count += outCode.length();
		}
	}

	return output;

}

/*vector<int> Huffman::strToVec(string s)
{
	vector<int> inputs;
	istringstream in(s);
	copy(istream_iterator<int>(in), istream_iterator<int>(), back_inserter(inputs));
	return inputs;
}*/

void Huffman::generateHeader() {
	string out = "";
	Node* tmp = root;

	header = "";
	stringstream ssheader;
	headerCount = 0;

	for (int i = 0; i < NUM_CHAR; i++)
	{
		if (charCount[i] > 0)
		{
			//header += to_string(i) + " " + to_string(charCount[i]) + " ";
			ssheader << i << " " << charCount[i] << " ";
			headerCount++;
		}
	}

	header = ssheader.str();

}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void Huffman::decode(char* f) {
	cout << f << endl;
	strToDecode = readHeader(f);
	root = buildMinHeap();
	writeTree(root);
	traverse();

	string fName = f;
	int noExt = fName.find_last_of(".");
	fName = fName.substr(0, noExt);

	ofstream fp;
	fp.open(fName.c_str(), ios_base::binary);
	fp << decodedStr;
	fp.close();

	remove(f);

}

string Huffman::readHeader(char* f) {

	ifstream fp;
	headerCount = 0;
	int loc;
	int number;
	string s;

	fp.open(f, ios_base::in | ios_base::binary);

	fp >> headerCount;

	for (int i = 0; i < headerCount; i++)
	{
		fp >> loc;
		fp >> number;
		charCount[loc] = number;
	}

	fp >> s;

	fp.close();

	return s;

}


void Huffman::traverse() {

	Node *tmp = root;

	for (int i = 0; i < strToDecode.length(); i++) {

		if (strToDecode[i] == '0'){
			tmp = tmp->left;
		}

		if (strToDecode[i] == '1'){
			tmp = tmp->right;
		}

		if (tmp->isLeaf())
		{
			decodedStr += (char)(tmp->data);
			tmp = root;
		}

	}

}
