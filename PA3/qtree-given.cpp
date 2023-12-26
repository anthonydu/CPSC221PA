/**
 * @file qtree-given.cpp
 * @description partial implementation of QTree class used for storing image data
 *              CPSC 221 PA3
 *
 *              THIS FILE WILL NOT BE SUBMITTED
 */

#include "qtree.h"

 /**
  * Node constructor.
  * Assigns appropriate values to all attributes.
  */
Node::Node(pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr, RGBAPixel a) {
	upLeft = ul;
	lowRight = lr;
	avg = a;

	NW = nullptr;
	NE = nullptr;
	SW = nullptr;
	SE = nullptr;
}

/**
 * QTree destructor.
 * Destroys all of the memory associated with the
 * current QTree. This function should ensure that
 * memory does not leak on destruction of a QTree.
 */
QTree::~QTree() {
	Clear();
}

/**
 * Copy constructor for a QTree. GIVEN
 * Since QTrees allocate dynamic memory (i.e., they use "new", we
 * must define the Big Three). This depends on your implementation
 * of the copy funtion.
 *
 * @param other The QTree  we are copying.
 */
QTree::QTree(const QTree& other) {
	Copy(other);
}

/**
 * Counts the number of nodes in the tree
 */
unsigned int QTree::CountNodes() const {
	return CountNodes(root);
}

/**
 * Counts the number of leaves in the tree
 */
unsigned int QTree::CountLeaves() const {
	return CountLeaves(root);
}

/**
 * Private helper function for counting the total number of nodes in the tree. GIVEN
 * @param nd the root of the subtree whose nodes we want to count
 */
unsigned int QTree::CountNodes(Node* nd) const {
	if (nd == nullptr)
		return 0;
	else
		return 1 + CountNodes(nd->NW) + CountNodes(nd->NE) + CountNodes(nd->SW) + CountNodes(nd->SE);
}

/**
 * Private helper function for counting the number of leaves in the tree. GIVEN
 * @param nd the root of the subtree whose leaves we want to count
 */
unsigned int QTree::CountLeaves(Node* nd) const {
	if (nd == nullptr)
		return 0;
	else {
		if (nd->NW == nullptr && nd->NE == nullptr && nd->SW == nullptr && nd->SE == nullptr)
			return 1;
		else
			return CountLeaves(nd->NW) + CountLeaves(nd->NE) + CountLeaves(nd->SW) + CountLeaves(nd->SE);
	}
}