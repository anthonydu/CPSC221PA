/**
 * File: block.cpp
 * Description: student implementation for Block functions
 *              for CPSC 221 2023W1 PA1
 *
 *              THIS FILE WILL BE SUBMITTED.
**/

#include "block.h"

/**
 * Creates a square Block that is dimension x dimension pixels in size,
 * starting at (x, y) on img. Assumes that the requested
 * Block fits on the image (inputs are feasible)
**/
void Block::Build(PNG& img, unsigned int x, unsigned int y, unsigned int dimension) {
	// complete your implementation below
    
}

/**
 * Renders this Block onto img with its upper-left corner at (x, y).
 * Assumes block fits on the image.
 * 
 * @param full - whether to render the entire contents to the target PNG,
 *               or the average color to a single pixel in the target PNG.
**/
void Block::Render(PNG& img, unsigned int x, unsigned int y, bool full) const {
	// complete your implementation below
    
}

/**
 * Flips the Block's pixel data horizontally by a simple reflection
 * across the vertical axis through its middle.
**/
void Block::FlipHorizontal() {
	// complete your implementation below
    
}

/**
 * Flips the Block's pixel data vertically by a simple reflection
 * across the horizontal axis through its middle.
**/
void Block::FlipVertical() {
	// complete your implementation below
    
}

/**
 * Returns the dimension of the block (its width or height).
 */
unsigned int Block::Dimension() const {
	// replace the statement below with your implementation
	return 0;
}

/**
 * Returns the average color of the pixels in the block's data.
**/
RGBAPixel Block::GetAverageColor() const {
	// replace the statement below with your implementation
	return RGBAPixel();
}

/**
 * Replaces all pixel data in the block with the block's average color.
**/
void Block::FillAverage() {
	// complete your implementation below
    
}