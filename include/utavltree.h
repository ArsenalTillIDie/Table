
#include "uttable.h"



template<class T> class DTree {
public:
	int d;
	std::vector<T> storage;
	int heapSize;
	DTree(std::vector<T> v, int dn) {
		storage = v;
		makeHeap();
		d = dn;
	}
	DTree(const DTree& tree) {
		storage = tree.storage;
		d = tree.d;
		heapSize = tree.heapSize;
	}
	int leftChild(int i) {
		if (i * d + 1 >= storage.size()) return -1;
		return i * d + 1;
	}
	int rightChild(int i) {
		if (i * d + 1 >= storage.size()) return -1;
		else if ((i + 1) * d < storage.size()) return (i + 1) * d;
		else return storage.size() - 1;
	}
	int parent(int i) {
		if (i == 0) return -1;
		else return (i - 1) / d;
	}
	int minChild(int i) {
		int minIndex = -1;
		if (leftChild(i) == -1) return -1;
		T min = storage[leftChild(i)];
		for (int j = leftChild(i); j <= rightChild(i); j++) {
			if (storage[j] <= min) {
				min = storage[j];
				minIndex = j;
			}
		}
		return minIndex;
	}
	void swap(int i, int j) {
		T temp = storage[i];
		storage[i] = storage[j];
		storage[j] = temp;
	}
	void dive(int i) {
		int j1 = i;
		int j2 = minChild(i);
		while (j2 != -1 && storage[j1] > storage[j2]) {
			swap(j1, j2);
			j1 = j2;
			j2 = minChild(j1);
		}
	}
	void emersion(int i) {
		int j1 = i;
		int j2 = parent(i);
		while (j2 != -1 && storage[j1] < storage[j2]) {
			swap(j1, j2);
			j1 = j2;
			j2 = parent(j1);
		}
	}
	void unconditionalEmersion(int i) {
		int j1 = i;
		int j2 = parent(i);
		while (j2 != -1) {
			swap(j1, j2);
			j1 = j2;
			j2 = parent(j1);
		}
	}
	void insert(int w) {  
		storage.push_back(w);
		emersion(storage.size() - 1);
	}
	void remove(int i) {
		unconditionalEmersion(i);
		deleteMin();
	}
	void deleteMin() {
		swap(0, storage.size() - 1);
		storage.pop_back();
		dive(0);
	}
	void decreaseWeight(int i, T delta) {
		storage[i] -= delta;
		emersion(i);
	}
	void makeHeap() { 
		for (int i = storage.size() - 1; i >= 0; i--)
			dive(i);
	}
	void heapsort() { 
		makeHeap();
		heapSize = storage.size();
		for (int i = 0; i < storage.size() - 1; i++) {
			swap(0, heapSize - 1);
			heapSize--;
			dive(0);
		}
	}

};

