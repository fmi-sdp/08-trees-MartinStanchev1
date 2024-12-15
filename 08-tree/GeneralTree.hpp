#pragma once

#include <iostream>
#include <queue>

template <typename T>
class GeneralTree {
private:
	struct node {
		T data;
		node* child;
		node* sibling;

		node(T data = T(), node* child = nullptr, node* sibling = nullptr)
			: data(data), child(child), sibling(sibling) {};
	};

public:
	GeneralTree();
	GeneralTree(T data, const GeneralTree& child = GeneralTree(), const GeneralTree& sibling = GeneralTree());
	GeneralTree(const GeneralTree& other);
	GeneralTree& operator=(const GeneralTree& other);
	~GeneralTree();

	bool empty() const;
	bool find(const T& key) const;
	bool remove(const T& key);
	size_t get_size() const;
	size_t get_height() const;

	template <typename Function>
	void map(const Function& f);

	void print();

	//4 zad
	size_t branchingCoefficient() const;
	//5 zad
	void printLevel(size_t n) const;
	//6 zad
	size_t leafCount() const;
private:
	static void clear(node* root);
	static typename GeneralTree<T>::node* copy(node* root);

	static bool find(const node* root, const T& key);
	static size_t height(const node* root);
	static bool remove(node*& root, const T& key);
	
	template <typename Function>
	void map(const Function& f, node* root);

	//4 zad
	static size_t branchingCoefficient(node* root);
	//5 zad
	static void printLevel(size_t n, node* root);
	//6 zad
	static size_t leafCount(node* root);
private:
	node* root;
	size_t size;
};

template<typename T>
inline GeneralTree<T>::GeneralTree()
	: root(nullptr), size(0) {}

template<typename T>
inline GeneralTree<T>::GeneralTree(T data, const GeneralTree& child, const GeneralTree& sibling) {
	root = new node(data, copy(child.root), copy(sibling.root));
}

template<typename T>
inline GeneralTree<T>::GeneralTree(const GeneralTree<T>& other)
	: root(copy(other.root))
	, size(other.size) {}

template<typename T>
inline GeneralTree<T>& GeneralTree<T>::operator=(const GeneralTree<T>& other) {
	if (this != &other) {
		clear(root);
		root = copy(other.root);
		size = other.size;
	}

	return *this;
}

template<typename T>
inline GeneralTree<T>::~GeneralTree() {
	clear(root);
}

template<typename T>
inline bool GeneralTree<T>::empty() const {
	return root == nullptr;
}

template<typename T>
inline bool GeneralTree<T>::find(const T& key) const {
	return find(root, key);
}

template<typename T>
inline bool GeneralTree<T>::remove(const T& key) {
	return remove(root, key);
}

template<typename T>
inline size_t GeneralTree<T>::get_size() const {
	return size;
}

template<typename T>
inline size_t GeneralTree<T>::get_height() const {
	return height(root);
}

template<typename T>
template<typename Function>
inline void GeneralTree<T>::map(const Function& f) {
	map(f, root);
}

template<typename T>
inline void GeneralTree<T>::print() {
	map([](const T& x)->void{ std::cout << x << ' '; });
	std::cout << std::endl;
}

template<typename T>
inline size_t GeneralTree<T>::branchingCoefficient() const
{
	return branchingCoefficient(root);
}

template<typename T>
inline void GeneralTree<T>::printLevel(size_t n) const
{
	printLevel(n, root);
	std::cout << std::endl;
}

template<typename T>
inline size_t GeneralTree<T>::leafCount() const
{
	return leafCount(root);
}

// Private methods
template<typename T>
inline void GeneralTree<T>::clear(node* root) {
	if (!root) return;

	clear(root->child);
	clear(root->sibling);
	delete root;
}

template<typename T>
inline typename GeneralTree<T>::node* GeneralTree<T>::copy(node* root) {
	if (!root)
		return root;

	return new
		node(root->data,
			copy(root->child),
			copy(root->sibling));
}

template<typename T>
inline bool GeneralTree<T>::find(const node* root, const T& key) {
	if (!root)
		return false;

	if (root->data == key)
		return true;

	return find(root->sibling, key)
		|| find(root->child, key);
}

template<typename T>
inline size_t GeneralTree<T>::height(const node* root) {
	if (!root)
		return 0;

	return std::max(
		1 + height(root->child),
		height(root->sibling));
}

template<typename T>
inline bool GeneralTree<T>::remove(node*& root, const T& key) {
	if (!root)
		return false;

	if (root->data != key)
		return remove(root->sibling, key)
		|| remove(root->child, key);

	node* to_delete = root;

	if (!root->child) {
		root = root->sibling;
	}
	else if (!root->sibling) {
		root = root->child;
	}
	else {
		node* it = root->child;
		while (it->sibling)
			it = it->sibling;

		it->sibling = root->sibling->child;
		root->sibling->child = root->child;
		root = root->sibling;
	}

	--size;
	delete to_delete;
	return true;
}

template<typename T>
inline size_t GeneralTree<T>::branchingCoefficient(node* root)
{
	if (!root)
		return 0;
	size_t rootCoeff = 0;
	node* currChild = root->child;
	while (currChild)
	{
		++rootCoeff;
		currChild = currChild->sibling;
	}
	return std::max(rootCoeff, std::max(branchingCoefficient(root->child), 
										branchingCoefficient(root->sibling)));
}
/*
template<typename T>
inline size_t GeneralTree<T>::branchingCoefficient(node* root) {
	if (!root)
		return 0;

	return std::max(
		1 + branchingCoefficient(root->sibling),
		branchingCoefficient(root->child)
	);
}*/

template<typename T>
inline void GeneralTree<T>::printLevel(size_t n, node* root)
{
	if (!root)
		return;
	node* currNode = root;
	if (n == 0)
	{
		while (currNode)
		{
			std::cout << currNode->data << " ";
			currNode = currNode->sibling;
		}
	}
	else
	{
		while (currNode)
		{
			printLevel(n - 1, currNode->child);
			currNode = currNode->sibling;
		}
	}
}

template<typename T>
inline size_t GeneralTree<T>::leafCount(node* root)
{
	if (!root)
		return 0;
	if (root->child == nullptr)
		return 1 + leafCount(root->sibling);
	return leafCount(root->child) + leafCount(root->sibling);
}

/*template<typename T>
inline size_t GeneralTree<T>::leafCount(node* root) {
	if (!root)
		return 0;

	if (!root->child)
		return 1;

	return leafCount(root->child) + leafCount(root->sibling);
}*/

template<typename T>
template<typename Function>
inline void GeneralTree<T>::map(const Function& f, node* root) {
	if (!root) return;

	f(root->data);
	map(f, root->sibling);
	map(f, root->child);
}