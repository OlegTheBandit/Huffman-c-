#include<iostream>

#pragma once	

#ifndef Node_h

using namespace std;

enum COLOR { RED, BLACK };


template<typename T1, typename T2>
class Node {

public:

	T1 key;

	T2 data;

	COLOR color;

	Node<T1, T2>* left, * right, * parent;


	
	Node(T1 key, T2 data) : key(key), data(data) {

		parent = left = right = NULL;



		// Node<T1, T2> is created during insertion 

		// Node<T1, T2> is 0 at insertion 

		color = RED;

	}


	~Node() = default;


	// returns pointer to uncle 

	Node<T1, T2>* uncle() {

		// If no parent or grandparent, then no uncle 

		if (parent == NULL || parent->parent == NULL)

			return NULL;



		if (parent->isOnLeft())

			// uncle on right 

			return parent->parent->right;

		else

			// uncle on left 

			return parent->parent->left;

	}



	// check if node is left child of parent 

	bool isOnLeft() { return this == parent->left; }



	// returns pointer to sibling 

	Node<T1, T2>* sibling() {

		// sibling null if no parent 

		if (parent == NULL)

			return NULL;



		if (isOnLeft())

			return parent->right;



		return parent->left;

	}



	// moves node down and moves given node in its place 

	void moveDown(Node<T1, T2>* nParent) {

		if (parent != NULL) {

			if (isOnLeft()) {

				parent->left = nParent;

			}
			else {

				parent->right = nParent;

			}

		}

		nParent->parent = parent;

		parent = nParent;

	}



	bool has0Child() {

		return (left != NULL && left->color == 0) ||

			(right != NULL && right->color == 0);

	}
};


#define Node_h
#endif //Node_h