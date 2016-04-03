
#include "Node.h"

using namespace std;

Node::Node() {
	
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