/**
 * @file qtree.cpp
 * @description student implementation of QTree class used for storing image
 * data CPSC 221 PA3
 *
 *              SUBMIT THIS FILE
 */

#include "qtree.h"

/**
 * Constructor that builds a QTree out of the given PNG.
 * Every leaf in the tree corresponds to a pixel in the PNG.
 * Every non-leaf node corresponds to a rectangle of pixels
 * in the original PNG, represented by an (x,y) pair for the
 * upper left corner of the rectangle and an (x,y) pair for
 * lower right corner of the rectangle. In addition, the Node
 * stores a pixel representing the average color over the
 * rectangle.
 *
 * The average color for each node in your implementation MUST
 * be determined in constant time. HINT: this will lead to nodes
 * at shallower levels of the tree to accumulate some error in their
 * average color value, but we will accept this consequence in
 * exchange for faster tree construction.
 * Note that we will be looking for specific color values in our
 * autograder, so if you instead perform a slow but accurate
 * average color computation, you will likely fail the test cases!
 *
 * Every node's children correspond to a partition of the
 * node's rectangle into (up to) four smaller rectangles. The node's
 * rectangle is split evenly (or as close to evenly as possible)
 * along both horizontal and vertical axes. If an even split along
 * the vertical axis is not possible, the extra line will be included
 * in the left side; If an even split along the horizontal axis is not
 * possible, the extra line will be included in the upper side.
 * If a single-pixel-wide rectangle needs to be split, the NE and SE children
 * will be null; likewise if a single-pixel-tall rectangle needs to be split,
 * the SW and SE children will be null.
 *
 * In this way, each of the children's rectangles together will have coordinates
 * that when combined, completely cover the original rectangle's image
 * region and do not overlap.
 */
QTree::QTree(const PNG& imIn) {
  // ADD YOUR IMPLEMENTATION BELOW
  width = imIn.width();
  height = imIn.height();
  root = BuildNode(imIn,
                   pair<unsigned int, unsigned int>(0, 0),
                   pair<unsigned int, unsigned int>(width - 1, height - 1));
}

/**
 * Overloaded assignment operator for QTrees.
 * Part of the Big Three that we must define because the class
 * allocates dynamic memory. This depends on your implementation
 * of the copy and clear funtions.
 *
 * @param rhs The right hand side of the assignment statement.
 */
QTree& QTree::operator=(const QTree& rhs) {
  // Replace the line below with your implementation
  Clear();
  Copy(rhs);
  return *this;
}

/**
 * Render returns a PNG image consisting of the pixels
 * stored in the tree. may be used on pruned trees. Draws
 * every leaf node's rectangle onto a PNG canvas using the
 * average color stored in the node.
 *
 * For up-scaled images, no color interpolation will be done;
 * each rectangle is fully rendered into a larger rectangular region.
 *
 * @param scale multiplier for each horizontal/vertical dimension
 * @pre scale > 0
 */
PNG QTree::Render(unsigned int scale) const {
  // Replace the line below with your implementation
  PNG img(width * scale, height * scale);
  Render(img, root, scale);
  return img;
}

/**
 *  Prune function trims subtrees as high as possible in the tree.
 *  A subtree is pruned (cleared) if all of the subtree's leaves are within
 *  tolerance of the average color stored in the root of the subtree.
 *  NOTE - you may use the distanceTo function found in RGBAPixel.h
 *  Pruning criteria should be evaluated on the original tree, not
 *  on any pruned subtree. (we only expect that trees would be pruned once.)
 *
 * You may want a recursive helper function for this one.
 *
 * @param tolerance maximum RGBA distance to qualify for pruning
 * @pre this tree has not previously been pruned, nor is copied from a
 * previously pruned tree.
 */
void QTree::Prune(double tolerance) {
  // ADD YOUR IMPLEMENTATION BELOW
  Prune(root, tolerance);
}

/**
 *  FlipHorizontal rearranges the contents of the tree, so that
 *  its rendered image will appear mirrored across a vertical axis.
 *  This may be called on a previously pruned/flipped/rotated tree.
 *
 *  After flipping, the NW/NE/SW/SE pointers must map to what will be
 *  physically rendered in the respective NW/NE/SW/SE corners, but it
 *  is no longer necessary to ensure that 1-pixel wide rectangles have
 *  null eastern children
 *  (i.e. after flipping, a node's NW and SW pointers may be null, but
 *  have non-null NE and SE)
 *
 *  You may want a recursive helper function for this one.
 */
void QTree::FlipHorizontal() {
  // ADD YOUR IMPLEMENTATION BELOW
  FlipHorizontal(root);
}

/**
 *  RotateCCW rearranges the contents of the tree, so that its
 *  rendered image will appear rotated by 90 degrees counter-clockwise.
 *  This may be called on a previously pruned/flipped/rotated tree.
 *
 *  Note that this may alter the dimensions of the rendered image, relative
 *  to its original dimensions.
 *
 *  After rotation, the NW/NE/SW/SE pointers must map to what will be
 *  physically rendered in the respective NW/NE/SW/SE corners, but it
 *  is no longer necessary to ensure that 1-pixel tall or wide rectangles
 *  have null eastern or southern children
 *  (i.e. after rotation, a node's NW and NE pointers may be null, but have
 *  non-null SW and SE, or it may have null NW/SW but non-null NE/SE)
 *
 *  You may want a recursive helper function for this one.
 */
void QTree::RotateCCW() {
  // ADD YOUR IMPLEMENTATION BELOW
  FlipHorizontal(root);
  FlipDiagonal(root);
  swap(width, height);
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current QTree object. Complete for PA3.
 * You may want a recursive helper function for this one.
 */
void QTree::Clear() {
  Clear(root);
}

/**
 * Copies the parameter other QTree into the current QTree.
 * Does not free any memory. Called by copy constructor and operator=.
 * You may want a recursive helper function for this one.
 * @param other The QTree to be copied.
 */
void QTree::Copy(const QTree& other) {
  root = new Node(other.root->upLeft, other.root->lowRight, other.root->avg);
  width = other.width;
  height = other.height;
  Copy(root, other.root);
}

/**
 * Private helper function for the constructor. Recursively builds
 * the tree according to the specification of the constructor.
 * @param img reference to the original input image.
 * @param ul upper left point of current node's rectangle.
 * @param lr lower right point of current node's rectangle.
 */
Node* QTree::BuildNode(const PNG& img,
                       pair<unsigned int, unsigned int> ul,
                       pair<unsigned int, unsigned int> lr) {
  // Replace the line below with your implementation
  auto min_x = ul.first;
  auto min_y = ul.second;
  if (ul == lr) return new Node(ul, lr, *(img.getPixel(min_x, min_y)));
  auto max_x = lr.first;
  auto max_y = lr.second;
  auto mid_x = min_x + (max_x - min_x) / 2;
  auto mid_y = min_y + (max_y - min_y) / 2;
  Node* NW = nullptr;
  Node* NE = nullptr;
  Node* SW = nullptr;
  Node* SE = nullptr;
  NW = BuildNode(img,
                 pair<unsigned int, unsigned int>(min_x, min_y),
                 pair<unsigned int, unsigned int>(mid_x, mid_y));
  if (min_x != max_x)
    NE = BuildNode(img,
                   pair<unsigned int, unsigned int>(mid_x + 1, min_y),
                   pair<unsigned int, unsigned int>(max_x, mid_y));
  if (min_y != max_y)
    SW = BuildNode(img,
                   pair<unsigned int, unsigned int>(min_x, mid_y + 1),
                   pair<unsigned int, unsigned int>(mid_x, max_y));
  if (min_x != max_x && min_y != max_y)
    SE = BuildNode(img,
                   pair<unsigned int, unsigned int>(mid_x + 1, mid_y + 1),
                   pair<unsigned int, unsigned int>(max_x, max_y));
  ;
  Node* node = new Node(ul, lr, Average((Node* [4]){NW, NE, SW, SE}));
  node->NW = NW;
  node->NE = NE;
  node->SW = SW;
  node->SE = SE;
  return node;
}

/*********************************************************/
/*** IMPLEMENT YOUR OWN PRIVATE MEMBER FUNCTIONS BELOW ***/
/*********************************************************/

unsigned int QTree::Area(pair<unsigned int, unsigned int> coord1,
                         pair<unsigned int, unsigned int> coord2) const {
  int x1 = coord1.first;
  int y1 = coord1.second;
  int x2 = coord2.first;
  int y2 = coord2.second;
  return (abs(x1 - x2) + 1) * (abs(y1 - y2) + 1);
}

unsigned int QTree::Area(Node* node) const {
  if (!node) std::cerr << "Area received nullptr";
  return Area(node->upLeft, node->lowRight);
}

RGBAPixel QTree::Average(Node* nodes[4]) const {
  int sum_r = 0;
  int sum_g = 0;
  int sum_b = 0;
  int total_area = 0;
  for (int i = 0; i < 4; i++) {
    Node* node = nodes[i];
    if (!node) continue;
    sum_r += node->avg.r * Area(node);
    sum_g += node->avg.g * Area(node);
    sum_b += node->avg.b * Area(node);
    total_area += Area(node);
  }
  int avg_r = sum_r / total_area;
  int avg_g = sum_g / total_area;
  int avg_b = sum_b / total_area;
  return RGBAPixel(avg_r, avg_g, avg_b);
}

void QTree::Render(PNG& img, Node* node, unsigned int scale) const {
  if (!node) return;
  auto min_x = node->upLeft.first;
  auto min_y = node->upLeft.second;
  auto max_x = node->lowRight.first;
  auto max_y = node->lowRight.second;
  for (auto x = min_x; x <= max_x; x++) {
    for (auto y = min_y; y <= max_y; y++) {
      for (unsigned int i = 0; i < scale; i++) {
        for (unsigned int j = 0; j < scale; j++) {
          *(img.getPixel(x * scale + i, y * scale + j)) = node->avg;
        }
      }
    }
  }
  Render(img, node->NW, scale);
  Render(img, node->NE, scale);
  Render(img, node->SW, scale);
  Render(img, node->SE, scale);
}

bool QTree::Prunable(Node* nd, RGBAPixel subRootAvg, double tolerance) const
{
  if (nd == nullptr) return true;
  if (!(nd->NW || nd->NE || nd->SW || nd->SE)) { // if nd is a leaf
    return (subRootAvg.distanceTo(nd->avg) < tolerance); 
  } else {
    bool pruneNW = Prunable(nd->NW, subRootAvg, tolerance);
    bool pruneNE = Prunable(nd->NE, subRootAvg, tolerance);
    bool pruneSW = Prunable(nd->SW, subRootAvg, tolerance);
    bool pruneSE = Prunable(nd->SE, subRootAvg, tolerance);
    return (pruneNW && pruneNE && pruneSW && pruneSE);
  }
}

void QTree::Prune(Node* nd, double tolerance) {
  if (nd == nullptr) return;
  if (Prunable(nd, nd->avg, tolerance)) {
    Clear(nd->NW);
    Clear(nd->NE);
    Clear(nd->SW);
    Clear(nd->SE);
    nd->NW = NULL;
    nd->NE = NULL;
    nd->SW = NULL;
    nd->SE = NULL;
  } else {
    Prune(nd->NW, tolerance);
    Prune(nd->NE, tolerance);
    Prune(nd->SW, tolerance);
    Prune(nd->SE, tolerance);
  }
}

void QTree::Prune(double tolerance, Node* node) {
  if (!node) return;
  vector<Node*> leaves;
  Leaves(node, leaves);
  bool prunable = true;
  for (Node* leaf : leaves) {
    if (node->avg.distanceTo(leaf->avg) >= tolerance) {
      prunable = false;
    }
  }
  if (prunable) {
    Clear(node->NW);
    Clear(node->NE);
    Clear(node->SW);
    Clear(node->SE);
    node->NW = nullptr;
    node->NE = nullptr;
    node->SW = nullptr;
    node->SE = nullptr;
  }
  Prune(tolerance, node->NW);
  Prune(tolerance, node->NE);
  Prune(tolerance, node->SW);
  Prune(tolerance, node->SE);
}

void QTree::Leaves(Node* node, vector<Node*>& leaves) const {
  if (!node) return;
  if (node->upLeft == node->lowRight) {
    leaves.push_back(node);
  }
  Leaves(node->NW, leaves);
  Leaves(node->NE, leaves);
  Leaves(node->SW, leaves);
  Leaves(node->SE, leaves);
}

void QTree::Copy(Node* c, Node* o) {
  if (o->NW) {
    c->NW = new Node(o->NW->upLeft, o->NW->lowRight, o->NW->avg);
    Copy(c->NW, o->NW);
  }
  if (o->NE) {
    c->NE = new Node(o->NE->upLeft, o->NE->lowRight, o->NE->avg);
    Copy(c->NE, o->NE);
  }
  if (o->SW) {
    c->SW = new Node(o->SW->upLeft, o->SW->lowRight, o->SW->avg);
    Copy(c->SW, o->SW);
  }
  if (o->SE) {
    c->SE = new Node(o->SE->upLeft, o->SE->lowRight, o->SE->avg);
    Copy(c->SE, o->SE);
  }
}

void QTree::Clear(Node* node) {
  if (!node) return;
  Clear(node->NW);
  Clear(node->NE);
  Clear(node->SW);
  Clear(node->SE);
  delete node;
}

void QTree::FlipHorizontal(Node* node) {
  if (!node) return;
  node->upLeft.first = width - node->upLeft.first - 1;
  node->lowRight.first = width - node->lowRight.first - 1;
  swap(node->upLeft.first, node->lowRight.first);
  swap(node->NW, node->NE);
  swap(node->SW, node->SE);
  FlipHorizontal(node->NW);
  FlipHorizontal(node->NE);
  FlipHorizontal(node->SW);
  FlipHorizontal(node->SE);
}

void QTree::FlipDiagonal(Node* node) {
  if (!node) return;
  swap(node->NE, node->SW);
  swap(node->upLeft.first, node->upLeft.second);
  swap(node->lowRight.first, node->lowRight.second);
  FlipDiagonal(node->NW);
  FlipDiagonal(node->NE);
  FlipDiagonal(node->SW);
  FlipDiagonal(node->SE);
}