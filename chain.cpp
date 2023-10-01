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
	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
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
	// the decision to make the pointers start from the both ends of each row is
	// because it provides the easiest way to detect when to move to the next row
	bool reachedLastRow = false;
	Node *pl = NW; // pointer left
	Node *pr = NW; // pointer right
	// move pr to the right most node of the first row
	for (int i = 0; i < cols - 1; i++)
		pr = pr->next;
	while (true)
	{
		// odd: if pl and pr meet
		if (pl == pr)
		{
			// flip the middle block
			pl->data.FlipHorizontal();
			// if this is the last row, break the loop
			if (reachedLastRow)
				break;
			// move pl to the left most node of the next row
			for (int i = 0; i <= cols / 2; i++)
				pl = pl->next;
			// move pr to the right most node of the next row
			for (int i = 0; i < cols / 2 + cols; i++)
				pr = pr->next;
			// if the next row is the last row, set reachedLastRow
			if (pr->next == NULL)
				reachedLastRow = true;
			// continue the loop without any swaps
			continue;
		}
		// even: if pr passes pl
		if (pl->prev == pr)
		{
			// if this is the last row, break the loop
			if (reachedLastRow)
				break;
			// move pl to the left most node of the next row
			for (int i = 0; i < cols / 2; i++)
				pl = pl->next;
			// move pr to the right most node of the next row
			for (int i = 0; i < cols / 2 + cols; i++)
				pr = pr->next;
			// if the next row is the last row, set reachedLastRow
			if (pr->next == NULL)
				reachedLastRow = true;
			// continue the loop without any swaps
			continue;
		}
		// swap the blocks
		Block left = pl->data;
		Block right = pr->data;
		pl->data = right;
		pr->data = left;
		// flip the blocks
		pl->data.FlipHorizontal();
		pr->data.FlipHorizontal();
		// move pl and pr towards the center
		pl = pl->next;
		pr = pr->prev;
	}
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
	// the decision to make the pointers start from the middle rows is
	// because it provides the easiest way to detect when we have reached the end
	// no matter if the number of rows is odd or even
	Node *pt = NW; // pointer top
	Node *pb = NW; // pointer bottom
	int rows = Length() / cols;
	// even
	if (rows % 2 == 0)
	{
		// move pt to the left most node of the upper middle row
		for (int i = 0; i < (rows / 2 - 1) * cols; i++)
			pt = pt->next;
		// move pb to the left most node of the lower middle row
		for (int i = 0; i < rows / 2 * cols; i++)
			pb = pb->next;
	}
	// odd
	else
	{
		// move pt and pb to the left most node of the middle row
		for (int i = 0; i < rows / 2 * cols; i++)
		{
			pt = pt->next;
			pb = pb->next;
		}
	}
	bool reachedLastPair = false;
	for (int x = 0; !reachedLastPair; x++)
	{
		// if the next col is the last col, set reachedLastPair
		if (pb->next == NULL)
			reachedLastPair = true;
		// if pt and pb reaches a new column
		if (x == cols)
		{
			x = 0;
			// move pt back two rows
			for (int i = 0; i < cols * 2; i++)
				pt = pt->prev;
		}
		// if pt and pb are not on the same row
		if (pt != pb)
		{
			// swap the blocks
			Block upper = pt->data;
			Block lower = pb->data;
			pt->data = lower;
			pb->data = upper;
			// prevent double flips
			pt->data.FlipVertical();
		}
		// flip the blocks
		pb->data.FlipVertical();
		// move pt and pb to the right
		pt = pt->next;
		pb = pb->next;
	}
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