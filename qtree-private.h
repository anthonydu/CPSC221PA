/**
 * @file qtree-private.h
 * @description student declaration of private QTree functions
 *              CPSC 221 PA3
 *
 *              SUBMIT THIS FILE.
 *
 *				Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

// begin your declarations below
void Render(PNG&, Node*, unsigned int) const;

void Prune(double, Node*);

void Leaves(Node*, vector<Node*>&) const;

unsigned int Area(Node*) const;

unsigned int Area(pair<unsigned int, unsigned int>,
                  pair<unsigned int, unsigned int>) const;

RGBAPixel Average(Node* [4]) const;

void Copy(Node*, Node*);

void Clear(Node*);

void FlipHorizontal(Node*);

void FlipDiagonal(Node*);