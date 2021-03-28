
#include <iostream>
#include <vector>

template<class T> struct Pair {
	unsigned int first;
	T second;
	Pair(unsigned int n1, T n2) {
		first = n1;
		second = n2;
	}
};

template<class T> class TableInterface {
protected:
	virtual unsigned int findIndex(unsigned int key) = 0;
public:
	virtual void insert(unsigned int key, const T& elem) = 0;
	virtual void erase(unsigned int key) = 0;
	virtual Pair<T>* find(unsigned int key) = 0;
	virtual size_t getSize() = 0;
	virtual void clear() = 0;
	virtual bool isEmpty() = 0;
};

template<class T> class TableByArray : public TableInterface<T> {
protected:
	std::vector<Pair<T>> storage;
	size_t size;
public:
	size_t getSize() override {
		return size;
	}
};

template<class T> class UnorderedTable : public TableByArray<T> {
private:
	unsigned int findIndex(unsigned int key) {
		for (int i = 0; i < size; i++)
			if (storage[i].first == key)
				return i;
		return -1;
	}
public:
	UnorderedTable() {
		storage = {};
		size = 0;
	}
	UnorderedTable(const UnorderedTable& tb) {
		storage = tb.storage;
		size = tb.size;
	}
	void insert(unsigned int key, const T& elem) {
		if (findIndex(key) != -1) throw "Element with given key already exists";
		storage.push_back(Pair<T>(key, elem));
		size++;
	}
	void erase(unsigned int key) {
		unsigned int index = findIndex(key);
		if (index == -1) throw "No field found with given key";
		storage[index] = storage[size - 1];
		storage.pop_back();
		size--;
	}
	Pair<T>* find(unsigned int key) {
		unsigned int index = findIndex(key);
		if (index == -1) throw "No field found with given key";
		else return &(storage[index]);
	}
	void clear() {
		for (int i = 0; i < size; i++)
			storage.pop_back();
		size = 0;
	}
	bool isEmpty() {
		if (size == 0) return true;
		else return false;
	}
};

template<class T> class OrderedTable : public TableByArray<T> {
private:
	unsigned int findIndex(unsigned int key) {
		int start = 0, end = size;
		while (end - start > 1) {
			int middle = (start + end) / 2;
			if (storage[middle].first == key)
				return middle;
			if (storage[middle].first < key)
				start = middle;
			else end = middle;
		}
		if (storage[start].first == key)
			return start;
		if (end >= size) return -1;
		if (storage[end].first == key)
			return end;
		return -1;
	}
public:
	OrderedTable() {
		storage = {};
		size = 0;
	}
	OrderedTable(const OrderedTable& tb) {
		storage = tb.storage;
		size = tb.size;
	}
	void insert(unsigned int key, const T& elem) {
		if (isEmpty()) {
			storage.push_back(Pair<T>(key, elem));
			size++;
			return;
		}
		int start = 0, end = size;
		while (end - start > 1) {
			int middle = (start + end) / 2;
			if (storage[middle].first == key)
				throw "Element with given key already exists";
			if (storage[middle].first < key)
				start = middle;
			else end = middle;
		}
		if (storage[start].first == key)
			throw "Element with given key already exists";
		if (end >= size) {
			storage.push_back(Pair<T>(key, elem));
			size++;
			return;
		}
		if (storage[end].first == key)
			throw "Element with given key already exists";
		if (storage[0].first > key)
			storage.insert(storage.begin(), Pair<T>(key, elem));
		else storage.insert(storage.begin() + end, Pair<T>(key, elem));
		size++;
	}
	void erase(unsigned int key) {
		unsigned int index = findIndex(key);
		if (index == -1) throw "No field found with given key";
		storage.erase(storage.begin() + index);
		size--;
	}
	Pair<T>* find(unsigned int key) {
		unsigned int index = findIndex(key);
		if (index == -1) throw "No field found with given key";
		else return &(storage[index]);
	}
	void clear() {
		for (int i = 0; i < size; i++)
			storage.pop_back();
		size = 0;
	}
	bool isEmpty() {
		if (size == 0) return true;
		else return false;
	}
};