
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
	void add(Node*); //Node parameter?
	bool isEmpty();
	int size();
	Node* peek(); //Node parameter?
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

/*

package huffman;

import java.util.Arrays;

public class heapPQueue<T extends Comparable<T>> {
private static final int DEFAULT_CAPACITY = 5;
protected T[] arr;
protected int numEls;


public heapPQueue () {

arr = (T[])new Comparable[DEFAULT_CAPACITY];
numEls = 0;
}

public void add(T value) {
// grow array if needed
if (numEls >= arr.length - 1) {
arr = this.resize();
}

numEls++;
int idx = numEls;
arr[idx] = value;

bubbleUp();
}



public boolean isEmpty() {
return numEls == 0;
}

public int size() {
return numEls;
}


public T peek() {
if (this.isEmpty()) {
throw new IllegalStateException();
}

return arr[1];
}


public T remove() {

T result = peek();

arr[1] = arr[numEls];
arr[numEls] = null;
numEls--;

bubbleDown();

return result;
}


public String toString() {
return Arrays.toString(arr);
}


protected void bubbleDown() {
int idx = 1;

while (hasLeftChild(idx)) {

int smallerChild = leftIndex(idx);

if (hasRightChild(idx) && arr[leftIndex(idx)].compareTo(arr[rightIndex(idx)]) > 0) {
smallerChild = rightIndex(idx);
}

if (arr[idx].compareTo(arr[smallerChild]) > 0) {
swap(idx, smallerChild);
} else {
break;
}

idx = smallerChild;
}
}


protected void bubbleUp() {
int index = this.numEls;

while (hasParent(index)
&& (parent(index).compareTo(arr[index]) > 0)) {

swap(index, parentIndex(index));
index = parentIndex(index);
}
}


protected boolean hasParent(int i) {
return i > 1;
}


protected int leftIndex(int i) {
return i * 2;
}


protected int rightIndex(int i) {
return i * 2 + 1;
}


protected boolean hasLeftChild(int i) {
return leftIndex(i) <= numEls;
}


protected boolean hasRightChild(int i) {
return rightIndex(i) <= numEls;
}


protected T parent(int i) {
return arr[parentIndex(i)];
}


protected int parentIndex(int i) {
return i / 2;
}


protected T[] resize() {
return Arrays.copyOf(arr, arr.length * 2);
}


protected void swap(int idx1, int idx2) {
T tmp = arr[idx1];
arr[idx1] = arr[idx2];
arr[idx2] = tmp;
}
}

*/

#endif

