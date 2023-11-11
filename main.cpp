/**
 * @file main.cpp
 * @description basic test cases for QTree
 *              CPSC 221 PA3
 * 
 *              You may add your own tests to this file
 *
 *              THIS FILE WILL NOT BE SUBMITTED
 */

#include <iostream>
#include <string>

#include "qtree.h"

using namespace std;

/**********************************/
/*** TEST FUNCTION DECLARATIONS ***/
/**********************************/
void TestBuildRender(unsigned int scale);
void TestFlipHorizontal();
void TestRotateCCW();
void TestPrune(double tol);

/***********************************/
/*** MAIN FUNCTION PROGRAM ENTRY ***/
/***********************************/

int main(int argc, char* argv[]) {

	TestBuildRender(1);
	TestBuildRender(6);
	TestFlipHorizontal();
	TestRotateCCW();
	TestPrune(0.01);
	TestPrune(0.05);

	return 0;
}

/*************************************/
/*** TEST FUNCTION IMPLEMENTATIONS ***/
/*************************************/

void TestBuildRender(unsigned int scale) {
	cout << "Entered TestBuildRender, scale: " << scale << endl;

	// read input PNG
	PNG input;
	input.readFromFile("images-original/malachi-60x87.png");

	cout << "Constructing QTree from image... ";
	QTree t(input);
	cout << "done." << endl;

	cout << "Rendering tree to PNG at x" << scale << " scale... ";
	PNG output = t.Render(scale);
	cout << "done." << endl;

	// write output PNG
	string outfilename = "images-output/malachi-render_x" + to_string(scale) + ".png";
	cout << "Writing rendered PNG to file... ";
	output.writeToFile(outfilename);
	cout << "done." << endl;

	cout << "Exiting TestBuildRender.\n" << endl;
}

void TestFlipHorizontal() {
	cout << "Entered TestFlipHorizontal" << endl;

	// read input PNG
	PNG input;
	input.readFromFile("images-original/malachi-60x87.png");

	cout << "Constructing QTree from image... ";
	QTree t(input);
	cout << "done." << endl;

	cout << "Calling FlipHorizontal... ";
	t.FlipHorizontal();
	cout << "done." << endl;

	cout << "Rendering tree to PNG at x1 scale... ";
	PNG output = t.Render(1);
	cout << "done." << endl;

	// write output PNG
	string outfilename = "images-output/malachi-fliphorizontal_x1-render_x1.png";
	cout << "Writing rendered PNG to file... ";
	output.writeToFile(outfilename);
	cout << "done." << endl;

	cout << "Calling FlipHorizontal a second time... ";
	t.FlipHorizontal();
	cout << "done." << endl;

	cout << "Rendering tree to PNG at x1 scale... ";
	output = t.Render(1);
	cout << "done." << endl;

	// write output PNG
	outfilename = "images-output/malachi-fliphorizontal_x2-render_x1.png";
	cout << "Writing rendered PNG to file... ";
	output.writeToFile(outfilename);
	cout << "done." << endl;

	cout << "Exiting TestFlipHorizontal.\n" << endl;
}

void TestRotateCCW() {
	cout << "Entered TestRotateCCW" << endl;

	// read input PNG
	PNG input;
	input.readFromFile("images-original/malachi-60x87.png");

	cout << "Constructing QTree from image... ";
	QTree t(input);
	cout << "done." << endl;

	cout << "Calling RotateCCW... ";
	t.RotateCCW();
	cout << "done." << endl;

	cout << "Rendering tree to PNG at x1 scale... ";
	PNG output = t.Render(1);
	cout << "done." << endl;

	// write output PNG
	string outfilename = "images-output/malachi-rotateccw_x1-render_x1.png";
	cout << "Writing rendered PNG to file... ";
	output.writeToFile(outfilename);
	cout << "done." << endl;

	cout << "Calling RotateCCW a second time... ";
	t.RotateCCW();
	cout << "done." << endl;

	cout << "Rendering tree to PNG at x1 scale... ";
	output = t.Render(1);
	cout << "done." << endl;

	// write output PNG
	outfilename = "images-output/malachi-rotateccw_x2-render_x1.png";
	cout << "Writing rendered PNG to file... ";
	output.writeToFile(outfilename);
	cout << "done." << endl;

	cout << "Calling RotateCCW a third time... ";
	t.RotateCCW();
	cout << "done." << endl;

	cout << "Rendering tree to PNG at x1 scale... ";
	output = t.Render(1);
	cout << "done." << endl;

	// write output PNG
	outfilename = "images-output/malachi-rotateccw_x3-render_x1.png";
	cout << "Writing rendered PNG to file... ";
	output.writeToFile(outfilename);
	cout << "done." << endl;

	cout << "Calling RotateCCW a fourth time... ";
	t.RotateCCW();
	cout << "done." << endl;

	cout << "Rendering tree to PNG at x1 scale... ";
	output = t.Render(1);
	cout << "done." << endl;

	// write output PNG
	outfilename = "images-output/malachi-rotateccw_x4-render_x1.png";
	cout << "Writing rendered PNG to file... ";
	output.writeToFile(outfilename);
	cout << "done." << endl;

	cout << "Exiting TestRotateCCW.\n" << endl;
}

void TestPrune(double tol) {
	cout << "Entered TestPrune, tolerance: " << tol << endl;

	// read input PNG
	PNG input;
	input.readFromFile("images-original/kkkk_nnkm-256x224.png");

	cout << "Constructing QTree from image... ";
	QTree t(input);
	cout << "done." << endl;

	cout << "Tree contains " << t.CountNodes() << " nodes and " << t.CountLeaves() << " leaves." << endl;

	cout << "Calling Prune... ";
	t.Prune(tol);
	cout << "done." << endl;

	cout << "Pruned tree contains " << t.CountNodes() << " nodes and " << t.CountLeaves() << " leaves." << endl;

	cout << "Rendering tree to PNG at x1 scale... ";
	PNG output = t.Render(1);
	cout << "done." << endl;

	// write output PNG
	string outfilename = "images-output/kkkk_nnkm-256x224-prune_" + to_string(tol) + "-render_x1.png";
	cout << "Writing rendered PNG to file... ";
	output.writeToFile(outfilename);
	cout << "done." << endl;

	cout << "Exiting TestPrune.\n" << endl;
}