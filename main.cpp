
// File:        main.cpp
// Author:      cheeren
// Date:        2021-02-20
// Description: Partial test of PA2 functionality
//

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "decoder.h"
#include "treasureMap.h"

using namespace cs221util;
using namespace std;

void testTreasureMapZdes();
void testTreasureMapDS();
void testTreasureMapSunshineMaze();
void testTreasureMapSunshineSnake();
void testDecoderZdes();
void testDecoderMaze();
void testDecoderSnake();

int main() {
  testTreasureMapZdes();

  testTreasureMapDS();

  testTreasureMapSunshineMaze();

  testTreasureMapSunshineSnake();

  testDecoderZdes();

  testDecoderMaze();

  testDecoderSnake();

  return 0;
}

void testTreasureMapZdes() {
  PNG maze;
  maze.readFromFile("images/zdesmaze.png");
  pair<int, int> start(69, 359);

  PNG base;
  base.readFromFile("images/zdesbase.png");

  treasureMap M(base, maze, start);

  PNG treasure = M.renderMap();
  treasure.writeToFile("output-images/zdesembedded.png");

  PNG treasuremaze = M.renderMaze();
  treasuremaze.writeToFile("output-images/zdesgreyedmaze.png");
}

void testTreasureMapDS() {
  PNG maze;
  maze.readFromFile("images/DSmaze.png");
  pair<int, int> start(313, 305);

  PNG base;
  base.readFromFile("images/DS.png");

  treasureMap M(base, maze, start);

  PNG treasure = M.renderMap();
  treasure.writeToFile("output-images/DSembedded.png");

  PNG treasuremaze = M.renderMaze();
  treasuremaze.writeToFile("output-images/DSgreyedmaze.png");
}

void testTreasureMapSunshineMaze() {
  PNG maze;
  maze.readFromFile("images/maze.png");
  pair<int, int> start(1, 1);

  PNG base;
  base.readFromFile("images/sunshine.png");

  treasureMap M(base, maze, start);

  PNG treasure = M.renderMap();
  treasure.writeToFile("output-images/mazeembedded.png");

  PNG treasuremaze = M.renderMaze();
  treasuremaze.writeToFile("output-images/mazegreyedmaze.png");
}

void testTreasureMapSunshineSnake() {
  PNG maze;
  maze.readFromFile("images/snake.png");
  pair<int, int> start(1, 1);

  PNG base;
  base.readFromFile("images/sunshine.png");

  treasureMap M(base, maze, start);

  PNG treasure = M.renderMap();
  treasure.writeToFile("output-images/snakeembedded.png");

  PNG treasuremaze = M.renderMaze();
  treasuremaze.writeToFile("output-images/snakegreyedmaze.png");
}

void testDecoderZdes() {
  PNG treasure;
  treasure.readFromFile("images/zdesembedded.png");
  pair<int, int> start(69, 359);

  decoder dec(treasure, start);

  PNG soln = dec.renderSolution();
  soln.writeToFile("output-images/zdessoln.png");

  PNG solnmaze = dec.renderMaze();
  solnmaze.writeToFile("output-images/zdessolnmaze.png");
}

void testDecoderMaze() {
  PNG treasure;
  treasure.readFromFile("images/embeddedmaze.png");
  pair<int, int> start(1, 1);

  decoder dec(treasure, start);

  PNG soln = dec.renderSolution();
  soln.writeToFile("output-images/mazesoln.png");

  PNG solnmaze = dec.renderMaze();
  solnmaze.writeToFile("output-images/mazesolnmaze.png");
}

void testDecoderSnake() {
  PNG treasure;
  treasure.readFromFile("images/embeddedsnake.png");
  pair<int, int> start(1, 1);

  decoder dec(treasure, start);

  PNG soln = dec.renderSolution();
  soln.writeToFile("output-images/snakesoln.png");

  PNG solnmaze = dec.renderMaze();
  solnmaze.writeToFile("output-images/snakesolnmaze.png");
}