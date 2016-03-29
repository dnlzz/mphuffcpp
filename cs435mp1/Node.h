#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node {

public:
	Node();
	Node(int, int, Node*, Node*);
	int data;
	int freq;
	Node* left;
	Node* right;
	bool isLeaf();
	int compareTo(Node*);
};

#endif