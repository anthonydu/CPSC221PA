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
void Block::Build(PNG &img, unsigned int x, unsigned int y, unsigned int dimension)
{
	data.clear();
	for (int i = x; i < x + dimension; i++)
	{
		vector<RGBAPixel> col;
		for (int j = y; j < y + dimension; j++)
		{
			col.push_back(*(img.getPixel(i, j)));
		}
		data.push_back(col);
	}
}

/**
 * Renders this Block onto img with its upper-left corner at (x, y).
 * Assumes block fits on the image.
 *
 * @param full - whether to render the entire contents to the target PNG,
 *               or the average color to a single pixel in the target PNG.
 **/
void Block::Render(PNG &img, unsigned int x, unsigned int y, bool full) const
{
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data.at(i).size(); j++)
		{
			*(img.getPixel(x + i, y + j)) = full ? data.at(i).at(j) : GetAverageColor();
		}
	}
}

/**
 * Flips the Block's pixel data horizontally by a simple reflection
 * across the vertical axis through its middle.
 **/
void Block::FlipHorizontal()
{
	int dim = data.size();
	for (int x = 0; x < dim / 2; x++)
	{
		vector<RGBAPixel> left = data.at(x);
		vector<RGBAPixel> right = data.at(dim - 1 - x);
		data.at(x) = right;
		data.at(dim - 1 - x) = left;
	}
}

/**
 * Flips the Block's pixel data vertically by a simple reflection
 * across the horizontal axis through its middle.
 **/
void Block::FlipVertical()
{
	int dim = data.size();
	for (int x = 0; x < dim; x++)
	{
		for (int y = 0; y < dim / 2; y++)
		{
			RGBAPixel upper = data.at(x).at(y);
			RGBAPixel lower = data.at(x).at(dim - 1 - y);
			data.at(x).at(y) = lower;
			data.at(x).at(dim - 1 - y) = upper;
		}
	}
}

/**
 * Returns the dimension of the block (its width or height).
 */
unsigned int Block::Dimension() const
{
	// replace the statement below with your implementation
	return 0;
}

/**
 * Returns the average color of the pixels in the block's data.
 **/
RGBAPixel Block::GetAverageColor() const
{
	int r = 0;
	int g = 0;
	int b = 0;
	int a = 0;
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data.at(i).size(); j++)
		{
			r += data.at(i).at(j).r;
			g += data.at(i).at(j).g;
			b += data.at(i).at(j).b;
			a += data.at(i).at(j).a;
		}
	}
	r /= data.size() * data.size();
	g /= data.size() * data.size();
	b /= data.size() * data.size();
	a /= data.size() * data.size();
	return RGBAPixel(r, g, b, a);
}

/**
 * Replaces all pixel data in the block with the block's average color.
 **/
void Block::FillAverage()
{
	RGBAPixel avg = GetAverageColor();
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data.at(i).size(); j++)
		{
			data.at(i).at(j) = avg;
		}
	}
}