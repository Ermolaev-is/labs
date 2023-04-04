#include "BinarySearchTree.h"
#include <iostream>

template <class T>
BinarySearchTree<T>::BinarySearchTree() : root_(nullptr) {}

template <class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& src) noexcept : root_(src.root_)
{
	src.root_ = nullptr;
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator= (BinarySearchTree<T>&& src) noexcept
{
	if (this != &src)
	{
		delete root_;
		root_ = src.root_;
		src.root_ = nullptr;
	}
	return *this;
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	deleteTree(root_);
}

template <class T>
bool BinarySearchTree<T>::iterativeSearch(const T& key) const
{
	return iterativeSearchNode(key) != nullptr;
}

template <class T>
bool BinarySearchTree<T>::insert(const T& key)
{
	Node* x = root_;
	Node* y = nullptr;

	while (x != nullptr)
	{
		y = x;
		if (key < x->key_)
		{
			x = x->left_;
		}
		else if (key > x->key_)
		{
			x = x->right_;
		}
		else
		{
			return false;
		}
	}

	Node* z = new Node(key, nullptr, nullptr, y);

	if (y == nullptr)
	{
		root_ = z;
	}
	else if (key < y->key_)
	{
		y->left_ = z;
	}
	else
	{
		y->right_ = z;
	}

	return true;
}

template <class T>
bool BinarySearchTree<T>::deleteKey(const T& key)
{
	Node* node = iterativeSearchNode(key);
	if (node == nullptr)
	{
		return false;
	}
	if (node->left_ == nullptr && node->right_ == nullptr)
	{
		if (node == root_)
		{
			root_ = nullptr;
		}
		else
		{
			if (node == node->p_->left_)
			{
				node->p_->left_ = nullptr;
			}
			else
			{
				node->p_->right_ = nullptr;
			}
		}
		delete node;
	}
	else if (node->left_ != nullptr && node->right_ == nullptr)
	{
		Node* child = node->left_;
		child->p_ = node->p_;
		if (node == root_)
		{
			root_ = child;
		}
		else
		{
			if (node == node->p_->left_)
			{
				node->p_->left_ = child;
			}
			else {
				node->p_->right_ = child;
			}
		}
		delete node;
	}
	else if (node->left_ == nullptr && node->right_ != nullptr)
	{
		Node* child = node->right_;
		child->p_ = node->p_;
		if (node == root_)
		{
			root_ = child;
		}
		else
		{
			if (node == node->p_->left_)
			{
				node->p_->left_ = child;
			}
			else
			{
				node->p_->right_ = child;
			}
		}
		delete node;
	}
	else
	{
		Node* successor = node->left_;
		while (successor->right_ != nullptr)
		{
			successor = successor->right_;
		}
		T k = successor->key_;
		deleteKey(successor->key_);
		node->key_ = k;
	}
	return true;
}

template <class T>
void BinarySearchTree<T>::print(std::ostream& out) const
{
	printNode(out, root_);
}

template <class T>
int BinarySearchTree<T>::getCount() const
{
	return getCount(this->root_);
}

template <class T>
int BinarySearchTree<T>::getHeight() const
{
	return getHeight(root_);
}

template <class T>
void BinarySearchTree<T>::iterativeInorderWalk() const
{
	if (root_ == nullptr)
	{
		return;
	}

	StackArray<Node*> s;
	Node* current = root_;

	while (current != nullptr || !s.isEmpty())
	{
		while (current != nullptr)
		{
			s.push(current);
			current = current->left_;
		}

		current = s.pop();
		std::cout << current->key_ << " ";

		current = current->right_;
	}
}

template <class T>
void BinarySearchTree<T>::inorderWalk() const
{
	inorderWalk(root_);
}

template <class T>
void BinarySearchTree<T>::walkByLevels() const
{
	if (root_ == nullptr)
	{
		return;
	}

	QueueArray<Node*> q;
	q.enQueue(root_);

	while (!q.isEmpty()) 
	{
		Node* curr = q.deQueue();

		std::cout << curr->key_ << " ";

		if (curr->left_ != nullptr) 
		{
			q.enQueue(curr->left_);
		}

		if (curr->right_ != nullptr) 
		{
			q.enQueue(curr->right_);
		}
	}
}

template <class T>
bool BinarySearchTree<T>::isSimilar(const BinarySearchTree<T>& other) const
{
	if (root_ == nullptr && other.root_ == nullptr)
	{
		return true;
	}
	else if (root_ == nullptr || other.root_ == nullptr)
	{
		return false;
	}

	StackArray<Node*> stack;
	Node* current = root_;
	while (!stack.isEmpty() || current != nullptr)
	{
		while (current != nullptr)
		{
			stack.push(current);
			current = current->left_;
		}
		current = stack.pop();
		if (!other.iterativeSearch(current->key_))
		{
			return false;
		}

		current = current->right_;
	}
	return true;
}

template <class T>
bool BinarySearchTree<T>::isIdenticalKey(const BinarySearchTree<T>& other) const
{
	if (root_ == nullptr || other.root_ == nullptr)
	{
		return false;
	}

	StackArray<Node*> stack;
	Node* current = root_;
	while (!stack.isEmpty() || current != nullptr)
	{
		while (current != nullptr)
		{
			stack.push(current);
			current = current->left_;
		}
		current = stack.pop();
		if (other.iterativeSearch(current->key_))
		{
			return true;
		}

		current = current->right_;
	}
	return false;
}

template <class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::iterativeSearchNode(const T& key) const
{
	Node* x = root_;

	while (x != nullptr && x->key_ != key)
	{
		if (key < x->key_)
		{
			x = x->left_;
		}
		else
		{
			x = x->right_;
		}
	}

	return x;
}

template <class T>
void BinarySearchTree<T>::printNode(std::ostream& out, Node* root) const
{
	if (root == nullptr)
	{
		out << "null";
		return;
	}

	out << "(" << root->key_ << " ";
	printNode(out, root->left_);
	out << " ";
	printNode(out, root->right_);
	out << ")";
}

template <class T>
int BinarySearchTree<T>::getCount(const Node* node) const
{
	if (node == nullptr)
	{
		return 0;
	}
	return (1 + getCount(node->left_) + getCount(node->right_));
}

template <class T>
int BinarySearchTree<T>::getHeight(const Node* node) const
{
	if (node == nullptr)
	{
		return 0;
	}
	else
	{
		int leftHeight = getHeight(node->left_);
		int rightHeight = getHeight(node->right_);
		return 1 + std::max(leftHeight, rightHeight);
	}
}

template <class T>
void BinarySearchTree<T>::inorderWalk(Node* node) const
{
	if (node != nullptr)
	{
		inorderWalk(node->left_);
		std::cout << node->key_ << " ";
		inorderWalk(node->right_);
	}
}

template <class T>
void BinarySearchTree<T>::deleteTree(Node* node)
{
	if (node != nullptr)
	{
		deleteTree(node->left_);
		deleteTree(node->right_);
		delete node;
	}
}