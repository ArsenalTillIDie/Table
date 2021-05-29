
#include <cmath>
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

template<class T>class TreeNode {
public:
	T data;
	TreeNode* left;
	TreeNode* right;
	TreeNode();
	TreeNode(const TreeNode<T>& n);
};

template<class T>TreeNode<T>::TreeNode() {
	left = nullptr;
	right = nullptr;
}
template<class T>TreeNode<T>::TreeNode(const TreeNode<T>& n) {
	data = n.data;
	left = n.left;
	right = n.right;
}

template<class T> class AVLTree {

private:
	int balanceFactor(TreeNode<Pair<T>>* current);
	int height(TreeNode<Pair<T>>* current);
	int leftHeight(TreeNode<Pair<T>>* current);
	int rightHeight(TreeNode<Pair<T>>* current);
	TreeNode<Pair<T>>* placeNode(Pair<T> elem, TreeNode<Pair<T>>* current);
	TreeNode<Pair<T>>* findAtNode(unsigned int key, TreeNode<Pair<T>>* current);
	void eraseBranch(TreeNode<Pair<T>>* current);
	void leftRotation(TreeNode<Pair<T>>* previous, bool isLeft);
	void rightRotation(TreeNode<Pair<T>>* previous, bool isLeft);
	void leftRightRotation(TreeNode<Pair<T>>* previous, bool isLeft);
	void rightLeftRotation(TreeNode<Pair<T>>* previous, bool isLeft);
	void balanceNode(TreeNode<Pair<T>>* previous, bool isLeft);
	void balanceRoot();
	void addToArray(std::vector<Pair<T>>& v, TreeNode<Pair<T>>* current);
public:
	TreeNode<Pair<T>>* root;
	AVLTree(std::vector<Pair<T>>& v);
	AVLTree(const AVLTree<T>& tree);
	~AVLTree();
	std::vector<Pair<T>> sort();
	TreeNode<Pair<T>>* find(unsigned int key);
	TreeNode<Pair<T>>* insert(Pair<T> elem);
	void erase(unsigned int key);
	bool isBalanced(TreeNode<Pair<T>>* current);
};

template<class T>int AVLTree<T>::balanceFactor(TreeNode<Pair<T>>* current) {
	return leftHeight(current) - rightHeight(current);
}
template<class T>int AVLTree<T>::height(TreeNode<Pair<T>>* current) {
	int lh = leftHeight(current), rh = rightHeight(current);
	if (lh > rh) {
		return lh + 1;
	}
	else return rh + 1;
}
template<class T>int AVLTree<T>::leftHeight(TreeNode<Pair<T>>* current) {
	if (current->left == nullptr) return 0;
	else return height(current->left);
}
template<class T>int AVLTree<T>::rightHeight(TreeNode<Pair<T>>* current) {
	if (current->right == nullptr) return 0;
	else return height(current->right);
}
template<class T>TreeNode<Pair<T>>* AVLTree<T>::placeNode(Pair<T> elem, TreeNode<Pair<T>>* current) {
	if (elem.first < current->data.first) {
		if (current->left == nullptr) {
			current->left = new TreeNode<Pair<T>>;
			current->left->data = elem;
			return current->left;
		}
		else {
			placeNode(elem, current->left);
			balanceNode(current, true);
		}
	}
	else {
		if (current->right == nullptr) {
			current->right = new TreeNode<Pair<T>>;
			current->right->data = elem;
			return current->right;
		}
		else {
			placeNode(elem, current->right);
			balanceNode(current, false);
		}
	}
}
template<class T>TreeNode<Pair<T>>* AVLTree<T>::findAtNode(unsigned int key, TreeNode<Pair<T>>* current) {
	if (key == current->data.first)
		return current;
	if (key < current->data.first) {
		if (current->left == nullptr) {
			throw "No element with given key found";
		}
		else findAtNode(key, current->left);
	}
	else {
		if (current->right == nullptr) {
			throw "No element with given key found";
		}
		else findAtNode(key, current->right);
	}
}
template<class T>void AVLTree<T>::eraseBranch(TreeNode<Pair<T>>* current) {
	if (current->left != nullptr) eraseBranch(current->left);
	if (current->right != nullptr) eraseBranch(current->right);
	delete current;
}

template<class T>void AVLTree<T>::leftRotation(TreeNode<Pair<T>>* previous, bool isLeft) {
	TreeNode<Pair<T>>* current;
	if (isLeft) {
		current = previous->left;
		previous->left = current->right;
	}
	else {
		current = previous->right;
		previous->right = current->right;
	}
	TreeNode<Pair<T>>* betweenCurrentAndRight = current->right->left;
	current->right->left = current;
	current->right = betweenCurrentAndRight;
}
template<class T>void AVLTree<T>::rightRotation(TreeNode<Pair<T>>* previous, bool isLeft) {
	TreeNode<Pair<T>>* current;
	if (isLeft) {
		current = previous->left;
		previous->left = current->left;
	}
	else {
		current = previous->right;
		previous->right = current->left;
	}
	TreeNode<Pair<T>>* betweenCurrentAndLeft = current->left->right;
	current->left->right = current;
	current->left = betweenCurrentAndLeft;
}
template<class T>void AVLTree<T>::leftRightRotation(TreeNode<Pair<T>>* previous, bool isLeft) {
	if (isLeft) leftRotation(previous->left, true);
	else leftRotation(previous->right, true);
	rightRotation(previous, isLeft);
}
template<class T>void AVLTree<T>::rightLeftRotation(TreeNode<Pair<T>>* previous, bool isLeft) {
	if (isLeft) rightRotation(previous->left, false);
	else rightRotation(previous->right, false);
	leftRotation(previous, isLeft);
}

template<class T>void AVLTree<T>::balanceNode(TreeNode<Pair<T>>* previous, bool isLeft) {
	TreeNode<Pair<T>>* current;
	if (isLeft) current = previous->left;
	else current = previous->right;
	if (isBalanced(current)) return;
	if (balanceFactor(current) > 1)
		if (balanceFactor(current->left) == 1) rightRotation(previous, isLeft);
		else leftRightRotation(previous, isLeft);
	else if (balanceFactor(current->right) == 1) rightLeftRotation(previous, isLeft);
	else leftRotation(previous, isLeft);
}
template<class T>void AVLTree<T>::addToArray(std::vector<Pair<T>>& v, TreeNode<Pair<T>>* current) {
	if (current->left != nullptr)
		addToArray(v, current->left);
	v.push_back(current->data);
	if (current->right != nullptr)
		addToArray(v, current->right);
}
template<class T>AVLTree<T>::AVLTree(std::vector<Pair<T>>& v) {
		root = new TreeNode<Pair<T>>;
		root->data = v[0];
		for (int i = 1; i < v.size(); i++) {
			insert(v[i]);
		}
	}
template<class T>AVLTree<T>::AVLTree(const AVLTree<T>& tree) {
		storage = tree.storage;
	}
template<class T>AVLTree<T>::~AVLTree() {
		eraseBranch(root);
	}

template<class T>std::vector<Pair<T>> AVLTree<T>::sort() {
		std::vector<Pair<T>> result;
		addToArray(result, root);
		return result;
	}
template<class T>TreeNode<Pair<T>>* AVLTree<T>::find(unsigned int key) {
		return findAtNode(key, root);
	}

template<class T>TreeNode<Pair<T>>* AVLTree<T>::insert(Pair<T> elem) {
		TreeNode<Pair<T>>* pn = placeNode(elem, root);
		TreeNode<Pair<T>> god;
		god.left = root;
		balanceNode(&god, true);
		root = god.left;
		return pn;
	}

template<class T>bool AVLTree<T>::isBalanced(TreeNode<Pair<T>>* current) {
		if (abs(balanceFactor(current)) > 1) return false;
		if (current->left != nullptr)
			if (!isBalanced(current->left)) return false;
		if (current->right != nullptr)
			if (!isBalanced(current->right)) return false;
		return true;
	}
	