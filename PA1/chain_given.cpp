/**
 * File: chain_given.cpp
 * Description: completed implementation for some Chain functions
 *              for CPSC 221 2023W1 PA1
 *
 *              THIS FILE WILL NOT BE SUBMITTED.
 */

#include "chain.h"

/**
 * Default Node constructor.
 */
Node::Node() : next(NULL), prev(NULL), data(Block()) {
	// nothing needed within body
}

/**
 * Parameterized Node constructor.
 */
Node::Node(const Block& ndata) : next(NULL), prev(NULL), data(ndata) {
	// nothing needed within body
}

/**
 * Default Chain constructor
 * Creates an empty Chain
 */
Chain::Chain() {
	NW = NULL;
	SE = NULL;
	length_ = 0;
}

/**
 * Default Chain constructor
 * Creates a Chain as a copy of other
 */
Chain::Chain(const Chain& other) {
	Copy(other);
}

/**
 * overloaded assignment operator
 * Allows statements of the form: mychain1 = mychain2;
 * Must deallocate any previously existing memory of this Chain.
 */
Chain& Chain::operator=(const Chain& rhs) {
	if (this != &rhs) {
		// this and rhs are not the same object in memory
		Clear();
		Copy(rhs);
	}
	return *this;
}

/**
 * Destructor
 */
Chain::~Chain() {
	Clear();
}

/**
 * Returns the number of Nodes in the Chain
 */
unsigned int Chain::Length() const {
	return length_;
}

/**
 * Returns true of the Chain is empty;
 * false otherwise
 */
bool Chain::IsEmpty() const {
	return (length_ == 0);
}