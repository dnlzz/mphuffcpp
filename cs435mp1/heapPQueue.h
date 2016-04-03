
#ifndef HEAPPQUEUE_H
#define HEAPPQUEUE_H

#include "Node.h"
#include <iostream>
#include <vector>
#include "Node.h"

using namespace std;

class heapPQueue {

public:
	heapPQueue();
	void add(Node*);
	bool isEmpty();
	int size();
	Node* peek();
	int numEls;
	vector<Node*> arr;
	Node* remove();
protected:
	void bubbleUp();
	void bubbleDown();
	bool hasParent(int);
	int leftIndex(int);
	int rightIndex(int);
	bool hasLeftChild(int);
	bool hasRightChild(int);
	Node* parent(int);
	int parentIndex(int);
	void swap(int, int);
	char* toString();
	void resize();
	
};

#endif

