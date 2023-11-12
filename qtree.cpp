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
  // ADD YOUR IMPLEMENTATION BELOW
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
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current QTree object. Complete for PA3.
 * You may want a recursive helper function for this one.
 */
void QTree::Clear() {
  // ADD YOUR IMPLEMENTATION BELOW
}

/**
 * Copies the parameter other QTree into the current QTree.
 * Does not free any memory. Called by copy constructor and operator=.
 * You may want a recursive helper function for this one.
 * @param other The QTree to be copied.
 */
void QTree::Copy(const QTree& other) {
  // ADD YOUR IMPLEMENTATION BELOW
}

/**
 * Private helper function for the constructor. Recursively builds
 * the tree according to the specification of the constructor.
 * @param img reference to the original input image.
 * @param ul upper left point of current node's rectangle.
 * @param lr lower right point of current node's rectangle.
 */
Node* QTree::BuildNode(const PNG& img, pair<unsigned int, unsigned int> ul,
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
  int num_children = 1;
  NW = BuildNode(img,
                 pair<unsigned int, unsigned int>(min_x, min_y),
                 pair<unsigned int, unsigned int>(mid_x, mid_y));
  if (min_x != max_x) {
    num_children++;
    NE = BuildNode(img,
                   pair<unsigned int, unsigned int>(mid_x + 1, min_y),
                   pair<unsigned int, unsigned int>(max_x, mid_y));
  }
  if (min_y != max_y) {
    num_children++;
    SW = BuildNode(img,
                   pair<unsigned int, unsigned int>(min_x, mid_y + 1),
                   pair<unsigned int, unsigned int>(mid_x, max_y));
  }
  if (min_x != max_x && min_y != max_y) {
    num_children++;
    SE = BuildNode(img,
                   pair<unsigned int, unsigned int>(mid_x + 1, mid_y + 1),
                   pair<unsigned int, unsigned int>(max_x, max_y));
  }
  auto avg_r = (NW->avg.r + (NE ? NE->avg.r : 0) + (SW ? SW->avg.r : 0)
                + (SE ? SE->avg.r : 0))
               / num_children;
  auto avg_g = (NW->avg.g + (NE ? NE->avg.g : 0) + (SW ? SW->avg.g : 0)
                + (SE ? SE->avg.g : 0))
               / num_children;
  auto avg_b = (NW->avg.b + (NE ? NE->avg.b : 0) + (SW ? SW->avg.b : 0)
                + (SE ? SE->avg.b : 0))
               / num_children;
  Node* node = new Node(ul, lr, RGBAPixel(avg_r, avg_g, avg_b));
  node->NW = NW;
  node->NE = NE;
  node->SW = SW;
  node->SE = SE;
  return node;
}

/*********************************************************/
/*** IMPLEMENT YOUR OWN PRIVATE MEMBER FUNCTIONS BELOW ***/
/*********************************************************/

void QTree::Render(const PNG& img, const Node* node, unsigned int scale) const {
  if (node->upLeft == node->lowRight) {
    auto x = node->upLeft.first * scale;
    auto y = node->upLeft.second * scale;
    for (int i = 0; i < scale; i++) {
      for (int j = 0; j < scale; j++) {
        *(img.getPixel(x + i, y + j)) = node->avg;
      }
    }
  } else {
    Render(img, node->NW, scale);
    if (node->NE) Render(img, node->NE, scale);
    if (node->SW) Render(img, node->SW, scale);
    if (node->SE) Render(img, node->SE, scale);
  }
}