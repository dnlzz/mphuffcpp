
#include "heapPQueue.h"

heapPQueue::heapPQueue() {
	arr;
	numEls = 0;
}

void heapPQueue::add(Node* value) {
	
	int idx = numEls;
	arr.push_back(value);
	numEls++;

	bubbleUp();

}



bool heapPQueue::isEmpty() {
	return numEls == 0;
}

int heapPQueue::size() {
	return numEls;
}


Node* heapPQueue::peek() {
	if (isEmpty()) {
		cerr << "Errrrr";
	}

	return arr[0];
}


Node* heapPQueue::remove() {

	Node* result = peek();

	arr[0] = arr[numEls-1];
	arr.pop_back();
	numEls--;

	bubbleDown();

	return result;
}


void heapPQueue::bubbleDown() {
	int idx = 0;

	while (hasLeftChild(idx)) {

		int smallerChild = leftIndex(idx);

		if (hasRightChild(idx) && arr[leftIndex(idx)]->compareTo(arr[rightIndex(idx)]) > 0) {
			smallerChild = rightIndex(idx);
		}

		if (arr[idx]->compareTo(arr[smallerChild]) > 0) {
			swap(idx, smallerChild);
		} else {
			break;
		}

		idx = smallerChild;
	}
}


void heapPQueue::bubbleUp() {
	int idx = numEls-1;

	while ( hasParent(idx) && ( parent(idx)->compareTo(arr[idx]) > 0) ) {
		swap(idx, parentIndex(idx));
		idx = parentIndex(idx);
	}
}


bool heapPQueue::hasParent(int i) {
	return i > 0;
}


int heapPQueue::leftIndex(int i) {
	return (i * 2) + 1;
}


int heapPQueue::rightIndex(int i) {
	return (i * 2) + 2;
}


bool heapPQueue::hasLeftChild(int i) {
	return leftIndex(i) < numEls;
}


bool heapPQueue::hasRightChild(int i) {
	return rightIndex(i) < numEls;
}


Node* heapPQueue::parent(int i) {
	return arr[parentIndex(i)];
}


int heapPQueue::parentIndex(int i) {
	return (i - 1) / 2;
}


void heapPQueue::swap(int idx1, int idx2) {
	Node *tmp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = tmp;
}
