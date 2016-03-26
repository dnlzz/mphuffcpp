
#include "Node.h"
#include <iostream>

using namespace std;

Node::Node() {
	cout << "Created:" << endl;
}

Node::Node(int newData, int newFreq, Node* newLeft, Node* newRight) {
		data = newData;
		freq = newFreq;
		left = newLeft;
		right = newRight;
	}

bool Node::isLeaf() {
	return (left == NULL) && (right == NULL);
}

int Node::compareTo(Node* other) {
	return this->freq - other->freq;
}