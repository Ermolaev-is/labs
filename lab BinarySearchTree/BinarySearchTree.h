#pragma once
#include <iostream>
#include "QueueArray.h"
#include "StackArray.h"

template <class T>
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<T>& scr) = delete;
	BinarySearchTree(BinarySearchTree<T>&& src) noexcept;
	BinarySearchTree<T>& operator= (const BinarySearchTree<T>& src) = delete;
	BinarySearchTree<T>& operator= (BinarySearchTree<T>&& src) noexcept;
	~BinarySearchTree();
	bool iterativeSearch(const T& key) const;
	bool insert(const T& key);
	bool deleteKey(const T& key);
	void print(std::ostream& out) const;
	int getCount() const;
	int getHeight() const;
	void iterativeInorderWalk() const;
	void inorderWalk() const;
	void walkByLevels() const;
	bool isSimilar(const BinarySearchTree<T>& other) const;
	bool isIdenticalKey(const BinarySearchTree<T>& other) const;
private:
	struct Node
	{
		T key_; 
		Node* left_; 
		Node* right_; 
		Node* p_; 
		Node(T key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr) :
			key_(key), left_(left), right_(right), p_(p)
		{ }
	};
	Node* iterativeSearchNode(const T& key) const;
	void printNode(std::ostream& out, Node* root) const;
	int getCount(const Node* node) const;
	int getHeight(const Node* node) const;
	void inorderWalk(Node* node) const;
	Node* root_; 
	void deleteTree(Node* node);
}; 

