/**
 * File: block.h
 * Description: declaration of a null-terminated, doubly-linked list node class
 *              for CPSC 221 2023W1 PA1
 *
 *              THIS FILE WILL NOT BE MODIFIED
**/

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"

using namespace std;
using namespace cs221util;

class Block {

private:
	vector<vector<RGBAPixel>> data;

public:
	/**
	 * Creates a square Block that is dimension x dimension pixels in size,
	 * starting at (x, y) on img. Assumes that the requested
	 * Block fits on the image (inputs are feasible)
	 */
	void Build(PNG& img, unsigned int x, unsigned int y, unsigned int dimension);

	/**
	 * Renders this Block onto img with its upper-left corner at (x, y).
	 * Assumes the rendered area fits on the image.
	 * 
	 * @param full - whether to render the entire contents to the target PNG,
	 *               or the average color to a single pixel in the target PNG.
	 */
	void Render(PNG& img, unsigned int x, unsigned int y, bool full) const;

	/**
	 * Flips the Block's pixel data horizontally by a simple reflection
	 * across the vertical axis through its middle.
	 */
	void FlipHorizontal();

	/**
	 * Flips the Block's pixel data vertically by a simple reflection
	 * across the horizontal axis through its middle.
	 */
	void FlipVertical();

	/**
	 * Returns the dimension of the block (its width or height).
	 */
	unsigned int Dimension() const;

	/**
	 * Returns the average color of the pixels in the block's data.
	**/
	RGBAPixel GetAverageColor() const;

	/**
	 * Replaces all pixel data in the block with the block's average color.
	**/
	void FillAverage();
};

#endif