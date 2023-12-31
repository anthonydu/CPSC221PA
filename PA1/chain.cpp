/**
 * File: chain.cpp
 * Description: student implementation for Chain functions
 *              for CPSC 221 2023W1 PA1
 *
 *              THIS FILE WILL BE SUBMITTED.
 **/

#include <math.h>
#include <iostream>

#include "chain.h"

using namespace std;

/**
 * Constructs a Chain from an input image
 * Each Node will cover a nodedimension x nodedimension (in pixels)
 * region in the source image.
 * @param img the input image
 * @param nodedimension number of pixels along the width and height of the Block region
 * @pre input image's width and height are evenly divisible by nodedimension
 **/
Chain::Chain(PNG &img, unsigned int nodedimension)
{
	length_ = 0;
	int cols = img.width() / nodedimension;
	int rows = img.height() / nodedimension;
	Node *prev = NULL;
	Node *node;
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			Block block;
			block.Build(img, x * nodedimension, y * nodedimension, nodedimension);
			node = new Node(block);
			node->prev = prev;
			if (prev)
				prev->next = node;
			else
				NW = node;
			prev = node;
			length_ += 1;
		}
	}
	node->next = NULL;
	SE = node;
}

/**
 * Renders the Chain's pixel data into an output PNG.
 * The PNG should be sized according to the number of nodes
 * specified by the cols parameter.
 * It is possible that there may not be enough nodes to fill
 * the bottom row of the PNG. If this happens, just render
 * as many nodes as there are, from left to right, and leave
 * the rest of the row as opaque white pixels.
 * @pre this Chain is not empty
 * @param cols the number of Blocks to use for the width of the image
 * @param full whether to render all pixel data into a full-size image,
 *             or block averages into a tiny image
 **/
PNG Chain::Render(unsigned int cols, bool full)
{
	if (!cols)
		return PNG();
	int rows = Length() / cols + (Length() % cols == 0 ? 0 : 1);
	PNG img(full ? cols * NodeDimension() : cols, full ? rows * NodeDimension() : rows);
	Node *curr = NW;
	unsigned x = 0;
	unsigned y = 0;
	while (curr)
	{
		if (full)
			curr->data.Render(img, x * NodeDimension(), y * NodeDimension(), true);
		else
			curr->data.Render(img, x, y, false);
		if (x == cols - 1)
		{
			y += 1;
			x = 0;
		}
		else
			x += 1;
		curr = curr->next;
	}
	return img;
}

/**
 * Inserts a new Node containing ndata at the back of the Chain
 **/
void Chain::InsertBack(const Block &ndata)
{
	Node *newNode = new Node(ndata);
	if (IsEmpty())
	{
		NW = newNode;
		SE = newNode;
		newNode->prev = NULL;
		newNode->next = NULL;
	}
	else
	{
		newNode->prev = SE;
		newNode->next = NULL;
		SE->next = newNode;
		SE = newNode;
	}
	length_ += 1;
}

/**
 * Reverses the structure of the list. This must be done by
 * pointer assignments. You may not deallocate or allocate any Nodes.
 * Example:
 *	before:	NW -> A <-> B <-> C <-> D <-> E <-> F <-> G <-> H <- SE
 *
 *  after:	NW -> H <-> G <-> F <-> E <-> D <-> C <-> B <-> A <- SE
 **/
void Chain::Reverse()
{
	Node *p = NW;
	while (p)
	{
		Node *next = p->next;
		Node *prev = p->prev;
		p->next = prev;
		p->prev = next;
		p = next;
	}
	Node *temp = NW;
	NW = SE;
	SE = temp;
}

/**
 * Rearranges the Node structure and internal pixel data to be flipped over a vertical axis.
 * This must be done using pointer assignments.
 * You may not deallocate or allocate any Nodes.
 * Example, length = 6:
 *  before, flipping with 3 columns (2 rows):
 *
 *		NW -> A> <-> B> <-> C> <->
 *            D> <-> E> <-> F> <- SE
 *
 *  after, visualized with 3 columns (2 rows):
 *
 *		NW -> <C <-> <B <-> <A <->
 *            <F <-> <E <-> <D <- SE
 *
 * @param cols number of Blocks to use for the initial width of the image
 * @pre length_ is divisible by cols (i.e. no "partially-filled" rows)
 **/
void Chain::FlipHorizontal(unsigned int cols)
{
	unsigned rows = Length() / cols;
	// keeps a copy of NW because we won't be able
	// to find it after we're done with the first row
	// (unless we get a pointer to come all the way back)
	Node *nwCopy;
	// for every row
	while (rows > 0)
	{
		// set p to the first node of the curr row
		Node *p = NW;
		// remember the last node of the prev row before moving p
		Node *lastOfPrevRow = p->prev;
		// move p to the last node of the curr row
		for (unsigned i = 1; i < cols; i++)
			p = p->next;
		// remember the first node of the next row before pointer reassignments
		Node *firstOfNextRow = p->next;
		// set SE to the last node of the curr row
		SE = p;
		// set both ends of the row to NULL
		SE->next = NULL;
		NW->prev = NULL;
		// reverse the current row
		Reverse();
		// if this is the first row, copy down NW
		if (rows == Length() / cols)
			nwCopy = NW;
		// if there is no next row, set SE, break
		if (firstOfNextRow == NULL)
		{
			SE->next = NULL;
			break;
		}
		// assign SE->next to the last node of the next row
		// because when the next row is flipped,
		// the last node will become the first node
		Node *lastOfNextRow = firstOfNextRow;
		for (unsigned i = 1; i < cols; i++)
			lastOfNextRow = lastOfNextRow->next;
		SE->next = lastOfNextRow;
		// set NW->prev to the last node of the prev row
		NW->prev = lastOfPrevRow;
		// set NW to the first node of the next row
		NW = firstOfNextRow;
		// one row done!
		rows -= 1;
	}
	// set NW to what it should be
	NW = nwCopy;
	// flip all node data
	FlipAll('h');
}

/**
 * Rearranges the Node structure and internal pixel data to be flipped over a horizontal axis.
 * This must be done using pointer assignments.
 * You may not deallocate or allocate any Nodes.
 * Example, length = 6:
 *	before, flipping with 3 columns (2 rows):
 *
 *      NW -> A <-> B <-> C <->
 *            D <-> E <-> F <- SE
 *
 *  after, visualized with 3 columns (2 rows):
 *
 *      NW -> D <-> E <-> F <->
 *            A <-> B <-> C <- SE
 *
 * @param cols number of Blocks to use for the initial width of the image
 * @pre length_ is divisible by cols (i.e. no "partially-filled" rows)
 **/
void Chain::FlipVertical(unsigned int cols)
{
	Reverse();
	FlipHorizontal(cols);
	FlipAll('h');
	FlipAll('v');
}

/**
 * Produces a blocky, pixellated effect (in a rendered image) by replacing each
 * block's pixel data with the average color of the block.
 **/
void Chain::Blockify()
{
	Node *p = NW;
	while (p)
	{
		p->data.FillAverage();
		p = p->next;
	}
}

/**
 * Destroys all dynamically allocated memory associated with
 * this Chain object. Called by destructor and operator=.
 * You must complete its implementation for PA1.
 **/
void Chain::Clear()
{
	Node *p = NW;
	while (p)
	{
		Node *next = p->next;
		delete p;
		p = next;
	}
	NW = NULL;
	SE = NULL;
	length_ = 0;
}

/**
 * Copies the parameter other Chain into the current Chain.
 * Does not free any memory. Called by copy constructor and
 * operator=.
 * You must complete its implementation for PA1.
 * @param other The Chain to be copied.
 **/
void Chain::Copy(const Chain &other)
{
	length_ = 0;
	Node *p = other.NW;
	while (p)
	{
		InsertBack(p->data);
		p = p->next;
	}
}

/**
 * If you have declared any private helper functions in chain_private.h,
 * add your completed implementations below.
 **/

int Chain::NodeDimension()
{
	if (IsEmpty())
	{
		cerr << "Cannot get node dimension of an empty chain!" << endl;
		return -1;
	}
	return NW->data.Dimension();
}

void Chain::FlipAll(char direction)
{
	Node *p = NW;
	while (p)
	{
		if (direction == 'h')
			p->data.FlipHorizontal();
		else
			p->data.FlipVertical();
		p = p->next;
	}
}