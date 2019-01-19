#ifndef BST_H
#define BST_H
#include "BSTInterface.h"

template<typename T>
class BST
{
private:
	struct Node
	{
		T data;
		Node* left;
		Node* right;
		Node(const T& d) : data(d), left(NULL), right(NULL) {}
		Node(const T& d, Node* l, Node* r) : data(d), left(l), right(r) {}
	};
	Node* root;
	size_t sizeTree;
public:
	BST() : root(NULL), sizeTree(0) {}
	~BST() { clearTree(); }

	/*
	class Iterator
	{
	private:
	// private iterator state...
	Node * current_;
	Node* root_;
	size_t sizeTree_;
	public:
	Iterator(Node* root) : current_(root), root_(root), sizeTree_() {}
	~Iterator() {}
	bool operator!=(const Iterator& other) const { return !(index_ == other.root_ && array_ == other.array_); }
	Iterator operator++(T) { ... }
	T operator*() const { ... }
	};
	Iterator begin() const { return root_; }
	Iterator end() const { return NULL; }
	*/

	/** Return true if node added to BST, else false */
	virtual bool addNode(const T& data)
	{
		return insert(root, data);
	}

	bool insert(Node*& node, const T& data)
	{
		if (node == NULL)
		{
			sizeTree++;
			node = new Node(data);
			//std::cout << "Added: " << data << std::endl;
			return true;
		}
		if (data == node->data)
		{
			return false;
		}
		if (data < node->data)
		{
			return insert(node->left, data);
		}
		if (data > node->data)
		{
			return insert(node->right, data);
		}
	}

	/** Return true if node removed from BST, else false */
	virtual bool removeNode(const T& val)
	{
		return remove(root, val);
	}

	bool remove(Node*& node, const T data)
	{
		if (node == NULL) return false;
		else if (data < node->data) return remove(node->left, data);
		else if (data > node->data) return remove(node->right, data);
		else
		{
			if (node->left == NULL && node->right == NULL)
			{
				delete node;
				node = NULL;
				std::cout << "Removed: " << data << std::endl;
				return true;
			}
			else if (node->left == NULL)
			{
				Node* temp = node;
				node = node->right;
				delete temp;
				std::cout << "Removed: " << data << std::endl;
				return true;
			}
			else if (node->right == NULL)
			{
				Node* temp = node;
				node = node->left;
				delete temp;
				std::cout << "Removed: " << data << std::endl;
				return true;
			}
			else
			{
				Node* in_order_predecessor = inOrderPredecessor(node->left);
				T temp = in_order_predecessor->data;
				in_order_predecessor->data = node->data;
				node->data = temp;
				return remove(node->left, data);
			}
		}
	}

	Node* inOrderPredecessor(Node* node)
	{
		Node* temp = node;
		while (temp->right != NULL)
		{
			temp = temp->right;
		}
		return temp;
	}


	/** Return true if BST cleared of all nodes, else false */
	virtual bool clearTree()
	{
		while (root != NULL)
		{
			removeNode(root->data);
		}
		return true;
	}

	size_t size() const { return getSize(root); }

	size_t getSize(Node* node) const
	{
		if (node == NULL) return 0;
		else return(getSize(node->left) + 1 + getSize(node->right));
	}

	bool find(T value)
	{
		return search(root, value);
	}

	bool search(Node* node, T value)
	{
		if (node == NULL)
		{
			return false;
		}
		if (node->data == value)
		{
			return true;
		}
		if (value < node->data)
		{
			return search(node->left, value);
		}
		if (value > node->data)
		{
			return search(node->right, value);
		}
	}

	/** Output nodes at a given level */
	bool outLevel(Node*& root, int level, std::stringstream& out) const
	{
		if (root == NULL) return false;
		if (level == 1)
		{
			out << " " << root->data;
			if ((root->left != NULL) || (root->right != NULL)) return true;
			return false;
		}
		if ((level == 2) && !root->left && root->right) out << " _";
		bool left = outLevel(root->left, level - 1, out);
		bool right = outLevel(root->right, level - 1, out);
		if ((level == 2) && root->left && !root->right) out << " _";
		return left || right;
	}

	void printInorder(Node* node, std::stringstream& out) 
	{
		if (node == NULL)
			return;

		/* first recur on left child */
		printInorder(node->left, out);

		/* then print the data of node */
		out << node->data << ",";

		/* now recur on right child */
		printInorder(node->right, out);
	}

	/** Return a level order traversal of a BST as a string */
	virtual std::string toString()
	{
		std::stringstream out;
		if (root == NULL) out << " Empty";
		else
		{
			printInorder(root, out);
		}
		std::string temp = out.str();
		temp.pop_back();
		return temp;

	}

};

#endif	// BST_INTERFACE_H