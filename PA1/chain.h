/**
 * File: chain.h
 * Description: declaration of a null-terminated, doubly-linked list class
 *              for CPSC 221 2023W1 PA1
 *
 *              THIS FILE WILL NOT BE SUBMITTED
 *
 *              IF YOU REQUIRE YOUR OWN PRIVATE FUNCTIONS,
 *              DECLARE THEM IN chain_private.h AND IMPLEMENT
 *              THEM IN chain.cpp
 */

#ifndef _CHAIN_H_
#define _CHAIN_H_

#include "block.h"

using namespace std;

/**
 * The Node class defines the components in the linked list chain.
 * Best practice implements this as a private class within the Chain class
 * since the end user does not need to know about the node-based
 * implementation details, but for the sake of testing in PrairieLearn,
 * this will be defined as a public class.
 */
class Node {
public:
	Node();						// default constructor - GIVEN
	Node(const Block& ndata);	// data provided constructor - GIVEN

	Node* next;			// pointer to next node in chain
	Node* prev;			// pointer to previous node in chain
	Block data;	// data held by this Node.
};

/**
 * Chain: This is a container class for Blocks. It is implemented as
 * a null-terminated, doubly-linked list of Nodes, each of which
 * contains a Block.
 * 
 * You should not change or remove anything from this class definition;
 * however, you may find it helpful to add your own private helper
 * functions. These should be added in the chain_private.h file.
 */
class Chain {
private:
	/**
	 * Private member variables.
	 * 
	 * These must be used according to the documented specification
	 * and may not be renamed or removed.
	 * If you wish to add more private member variables, add them
	 * into chain_private.h.
	 */
	Node* NW;	// pointer to the northwest node; the first node in the list
	Node* SE;	// pointer to the southeast node; the last node in the list

	unsigned int length_;	// counts the number of nodes in the Chain.

public:
	Chain();					// default constructor - GIVEN
	Chain(PNG& img, unsigned int nodedimension);	// parameterized constructor - TO BE IMPLEMENTED
	Chain(const Chain& other);	// copy constructor - GIVEN

	Chain& operator=(const Chain& rhs);	// overloaded assignment operator - GIVEN

	~Chain();	// destructor - GIVEN

	unsigned int Length() const;	// returns number of nodes in the Chain - GIVEN
	bool IsEmpty() const;			// checks if the Chain contains no Nodes - GIVEN
	PNG Render(unsigned int cols, bool full);	// Renders Chain's pixel data to an output image - TO BE IMPLEMENTED

	void InsertBack(const Block& ndata);	// adds a Node to the end of the Chain - TO BE IMPLEMENTED
	void Reverse();			// Reverses the Node structure of the list - TO BE IMPLEMENTED
	void FlipHorizontal(unsigned int cols);  // Rearranges the Node structure and internal pixel data to be flipped over a vertical axis - TO BE IMPLEMENTED
	void FlipVertical(unsigned int cols);		// Rearranges the Node structure and internal pixel data to be rotated counter-clockwise - TO BE IMPLEMENTED
	void Blockify();    // Creates a blocky pixel effect by coloring each block with its corresponding average color - TO BE IMPLEMENTED

private:
	/**
	 * Private helper functions
	 * These can only be called from within other Chain functions.
	 * If you wish to add more private helper functions, add them
	 * into chain_private.h.
	 */

	/**
	 * Destroys all dynamically allocated memory associated with
	 * this Chain object. Called by destructor and operator=.
	 * You must complete its implementation for PA1.
	 */
	void Clear();

	/**
	 * Copies the parameter other Chain into the current Chain.
	 * Does not free any memory. Called by copy constructor and
	 * operator=.
	 * You must complete its implementation for PA1.
	 * @param other The Chain to be copied.
	 */
	void Copy(const Chain& other);

	/**
	 * inclusion of student-defined private attributes and functions
	 */
	#include "chain_private.h"
};

#endif