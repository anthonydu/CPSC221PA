/**
 * File: main.cpp
 * Description: entry point for test program
 *              for CPSC 221 2023W1 PA1
 *
 *              Add or modify test code as needed.
 *
 *              THIS FILE WILL NOT BE SUBMITTED.
 */

#include <iostream>

#include "chain.h"

using namespace std;
using namespace cs221util;

/**
 * Test function declarations
 */

void TestChainRenderFull();
void TestChainRenderTiny();
void TestChainReverse();
void TestChainFlipHorizontal();
void TestChainFlipVertical();
void TestChainBlockify();
void TestBlock();
void TestChain();

/**
 * Program entry point
 */
int main(void)
{

	// add or remove calls to testing functions as needed
	TestChainRenderFull();
	cout << "TestChainRenderFull completed.\n"
			 << endl;
	TestChainRenderTiny();
	cout << "TestChainRenderTiny completed.\n"
			 << endl;
	TestChainReverse();
	cout << "TestChainReverse completed.\n"
			 << endl;
	TestChainFlipHorizontal();
	cout << "TestChainFlipHorizontal completed.\n"
			 << endl;
	TestChainFlipVertical();
	cout << "TestChainFlipVertical completed.\n"
			 << endl;
	TestChainBlockify();
	cout << "TestChainBlockify completed.\n"
			 << endl;
	TestBlock();
	cout << "TestBlock completed.\n"
			 << endl;
	TestChain();
	cout << "TestChain completed.\n"
			 << endl;

	return 1;
}

/**
 * Test function implementations
 */

void TestChainRenderFull()
{
	cout << "Entered TestChainRenderFull." << endl;
	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Rendering Chain to output PNG with 2 columns... ";
	PNG alphabet2 = c.Render(2, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet2.writeToFile("images-output/alphabet-240x40-render2-full.png");
	cout << "done." << endl;

	cout << "Rendering Chain to output PNG with 3 columns... ";
	PNG alphabet3 = c.Render(3, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet3.writeToFile("images-output/alphabet-240x40-render3-full.png");
	cout << "done." << endl;

	cout << "Rendering Chain to output PNG with 4 columns... ";
	PNG alphabet4 = c.Render(4, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet4.writeToFile("images-output/alphabet-240x40-render4-full.png");
	cout << "done." << endl;

	cout << "Leaving TestChainRenderFull..." << endl;
}

void TestChainRenderTiny()
{
	cout << "Entered TestChainRenderTiny." << endl;
	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Rendering Chain to output PNG with 4 columns... ";
	PNG alphabet4 = c.Render(4, false);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabet4.writeToFile("images-output/alphabet-240x40-render4-tiny.png");
	cout << "done." << endl;

	cout << "Leaving TestChainRenderTiny..." << endl;
}

void TestChainReverse()
{
	cout << "Entered TestChainReverse." << endl;

	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Calling Reverse... ";
	c.Reverse();
	cout << "done." << endl;

	cout << "Rendering reversed Chain to output PNG with 6 columns... ";
	PNG alphabetreversed = c.Render(6, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabetreversed.writeToFile("images-output/alphabet-240x40-reverse-render6.png");
	cout << "done." << endl;

	cout << "Leaving TestChainReverse..." << endl;
}

void TestChainFlipHorizontal()
{
	cout << "Entered TestChainFlipHorizontal." << endl;
	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Calling FlipHorizontal with 3 columns... ";
	c.FlipHorizontal(3);
	cout << "done." << endl;

	cout << "Rendering flipped Chain to output PNG with 3 columns... ";
	PNG alphabetflipped = c.Render(3, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabetflipped.writeToFile("images-output/alphabet-240x40-fliph3-render3-full.png");
	cout << "done." << endl;

	cout << "Leaving TestChainFlipHorizontal..." << endl;
}

void TestChainFlipVertical()
{
	cout << "Entered TestChainFlipVertical." << endl;
	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Calling FlipVertical with 3 columns... ";
	c.FlipVertical(3);
	cout << "done." << endl;

	cout << "Rendering flipped Chain to output PNG with 3 columns... ";
	PNG alphabetflipped = c.Render(3, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabetflipped.writeToFile("images-output/alphabet-240x40-flipv3-render3-full.png");
	cout << "done." << endl;

	cout << "Leaving TestChainFlipVertical..." << endl;
}

void TestChainBlockify()
{
	cout << "Entered TestChainBlockify." << endl;
	// load a PNG file
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	cout << "Creating a Chain from PNG... ";
	Chain c(alphabetpng, 40);
	cout << "done." << endl;

	cout << "Calling Blockify... ";
	c.Blockify();
	cout << "done." << endl;

	cout << "Rendering flipped Chain to output PNG with 3 columns... ";
	PNG alphabetblocky = c.Render(3, true);
	cout << "done." << endl;

	cout << "Writing output PNG to file... ";
	alphabetblocky.writeToFile("images-output/alphabet-240x40-blockify-render3-full.png");
	cout << "done." << endl;

	cout << "Leaving TestChainBlockify..." << endl;
}

void TestBlock()
{
	PNG alphabetpng;
	PNG output(40, 40);
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");
	Block block;
	block.Build(alphabetpng, 0, 0, 40);
	block.Render(output, 0, 0, true);
	output.writeToFile("images-output/block-output/a.png");
	block.Build(alphabetpng, 200, 0, 40);
	block.Render(output, 0, 0, true);
	output.writeToFile("images-output/block-output/f.png");

	block.FlipHorizontal();
	block.Render(output, 0, 0, true);
	output.writeToFile("images-output/block-output/f-flip-h.png");

	block.FlipHorizontal();
	block.FlipVertical();
	block.Render(output, 0, 0, true);
	output.writeToFile("images-output/block-output/f-flip-v.png");
}

void TestChain()
{
	PNG alphabetpng;
	alphabetpng.readFromFile("images-original/alphabet-240x40.png");

	Chain other(alphabetpng, 40);
	Chain copy(other);

	PNG o = other.Render(4, true);
	o.writeToFile("images-output/chain-output/other.png");
	PNG c = copy.Render(4, true);
	c.writeToFile("images-output/chain-output/copy.png");

	PNG tall = other.Render(1, true);
	tall.writeToFile("images-output/chain-output/tall.png");
	PNG zero = other.Render(0, true);
	zero.writeToFile("images-output/chain-output/zero.png");
	PNG wide = other.Render(10, true);
	wide.writeToFile("images-output/chain-output/wide.png");

	Chain chain;
	chain = Chain(alphabetpng, 40);
	chain.FlipHorizontal(1);
	chain.Render(1, true).writeToFile("images-output/chain-output/h1.png");
	chain = Chain(alphabetpng, 40);
	chain.FlipVertical(1);
	chain.Render(1, true).writeToFile("images-output/chain-output/v1.png");
	chain = Chain(alphabetpng, 40);
	chain.FlipHorizontal(2);
	chain.Render(2, true).writeToFile("images-output/chain-output/h2.png");
	chain = Chain(alphabetpng, 40);
	chain.FlipVertical(2);
	chain.Render(2, true).writeToFile("images-output/chain-output/v2.png");
	chain = Chain(alphabetpng, 40);
	chain.FlipHorizontal(3);
	chain.Render(3, true).writeToFile("images-output/chain-output/h3.png");
	chain = Chain(alphabetpng, 40);
	chain.FlipVertical(3);
	chain.Render(3, true).writeToFile("images-output/chain-output/v3.png");
	chain = Chain(alphabetpng, 40);
	chain.FlipHorizontal(6);
	chain.Render(6, true).writeToFile("images-output/chain-output/h6.png");
	chain = Chain(alphabetpng, 40);
	chain.FlipVertical(6);
	chain.Render(6, true).writeToFile("images-output/chain-output/v6.png");

	Chain one(alphabetpng, 20);
	one.Render(6, true).writeToFile("images-output/chain-output/one.png");

	Chain newChain;
	Block block;
	block.Build(alphabetpng, 0, 0, 40);
	newChain.InsertBack(block);
	newChain.FlipHorizontal(1);
	newChain.Render(1, true).writeToFile("images-output/chain-output/1h.png");
	newChain.FlipHorizontal(1);
	newChain.FlipVertical(1);
	newChain.Render(1, true).writeToFile("images-output/chain-output/1v.png");
}