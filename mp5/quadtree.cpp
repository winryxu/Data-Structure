/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include "quadtree.h"
#include <iostream>
#include <math.h>
using namespace std;

/* default constructor*/
Quadtree::Quadtree()
{
  root = NULL;
  size = 0;
}
/* constructor */
Quadtree::Quadtree(PNG const &source, int resolution)
{
  root = NULL;
  size = resolution;
  //cout<<"line 21 cpp"<<endl;
  buildTree(source,resolution);
}
/* copy constructor */
Quadtree::Quadtree(Quadtree const &other)
{
  copy(other);
}
/* copy constructor helper function*/
void Quadtree::copy(Quadtree const &other)
{
  // if other is NULL
  if (other.root == NULL)
  {
    root = NULL;
    size = other.size;
    return;
  }
  size = other.size;
  copy(other.root,root);
}

/* Copy constructor helper function to recursively copy the node*/
void Quadtree::copy(QuadtreeNode* const &other, QuadtreeNode* & q)
{
  if (other == NULL) return;
  // create a new root
  q = new QuadtreeNode(other->element);
  // q->element.red = other->element.red;
  // q->element.green = other->element.green;
  // q->element.blue = other->element.blue;
  // q->element.alpha = other->element.alpha;
  //q->element = other->element;
  // recursively copy
  if (other->nwChild != NULL)
  {
    copy(other->nwChild,q->nwChild);
    copy(other->neChild,q->neChild);
    copy(other->swChild,q->swChild);
    copy(other->seChild,q->seChild);
  }
}

Quadtree::QuadtreeNode::QuadtreeNode()
{
  //default constructor for QuadtreeNode
  nwChild = NULL;
  neChild = NULL;
  swChild = NULL;
  seChild = NULL;
}

/*constructor with argument of QuadtreeNode*/
Quadtree::QuadtreeNode::QuadtreeNode(RGBAPixel elem)
{
  nwChild = NULL;
  neChild = NULL;
  swChild = NULL;
  seChild = NULL;
  element = elem;
}

void Quadtree::buildTree(PNG const &source, int resolution)
{
  //check for boundary
  // delete the current node
  clear(root);
  root = NULL;
  size = resolution;
  root = buildTreeHelper(source, 0, 0, resolution);
}

Quadtree::QuadtreeNode* Quadtree::buildTreeHelper( PNG const &source, int x, int y, int resolution)
{
  //base case resolution == 1 and resolution ==0
  if (resolution == 0) return NULL;
  if (resolution == 1)
  {
    QuadtreeNode* temp = new QuadtreeNode(*source(x,y));
    //temp->element = *source(x,y);
    return temp;
  }
  //cout<<"build tree line96"<<endl;
  QuadtreeNode* temproot = new QuadtreeNode();
  // assign children, call buildTreeHelper
  temproot->nwChild = buildTreeHelper(source, x, y, resolution/2);
  temproot->neChild = buildTreeHelper(source, x+resolution/2, y,resolution/2);
  temproot->swChild = buildTreeHelper(source, x,y+resolution/2,resolution/2);
  temproot->seChild = buildTreeHelper(source, x+resolution/2,y+resolution/2,resolution/2);
  // average element's rgba
  temproot->element.red = (temproot->nwChild->element.red + temproot->neChild->element.red
                          + temproot->swChild->element.red + temproot->seChild->element.red)/4;
  temproot->element.green = (temproot->nwChild->element.green + temproot->neChild->element.green
                          + temproot->swChild->element.green + temproot->seChild->element.green)/4;
  temproot->element.blue = (temproot->nwChild->element.blue + temproot->neChild->element.blue
                          + temproot->swChild->element.blue + temproot->seChild->element.blue)/4;


  return temproot;
}


Quadtree Quadtree::operator= (Quadtree const& other)
{
  // if this and other is not on the same address
  if (this != &other)
  {
    clear(root);
    copy(other);
  }
  return *this;
}

Quadtree::~Quadtree()
{
  clear(root);
  size = 0;
}

void Quadtree::clear(QuadtreeNode*& node)
{
  // Base case : if node is NULL, do nothing
  if (node == NULL) return;
  // recursively clear
  if (node->nwChild != NULL)
  {
    clear(node->nwChild);
    clear(node->neChild);
    clear(node->swChild);
    clear(node->seChild);
  }
  //delete current node
  delete node;
  //node = NULL;
}

RGBAPixel Quadtree::getPixel(int x, int y) const
{
  // check for boundary
  if (x > size || y > size || root == NULL)
  {
    return RGBAPixel();
  }
  return getPixelHelper(x,y,root,size);
}

RGBAPixel Quadtree::getPixelHelper(int x, int y, QuadtreeNode* node, int d) const
{
  if (x > d || y > d || node == NULL || x < 0 || y < 0) return RGBAPixel();
  if (node->nwChild == NULL)
  {
    return node->element;
  }
  // try to reduce the run time for getPixel
  if (x < d/2)
  {
    // goes to nwChild
    if (y < d/2)
      return getPixelHelper(x,y,node->nwChild,d/2);
    // goes to swChild
    else //if (y >= d/2)
      return getPixelHelper(x ,y - d/2,node->swChild,d/2);
  }

  else //if (x >= d/2)
  {
    // goes to neChild
    if (y < d/2)
      return getPixelHelper(x - d/2,y,node->neChild,d/2);
    // goes to seChild
    else //if (y >= d/2)
      return getPixelHelper(x - d/2,y - d/2,node->seChild,d/2);
  }
}

PNG Quadtree::decompress() const
{
  // if root is NULL
  if (root == NULL)
  {
    PNG temp;
    return temp;
  }

  // create a PNG with size*size dimension
  PNG temp(size, size);

  // copy pixel to PNG
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
        *(temp(i,j)) = getPixel(i,j);
    }
  }
  return temp;
}


void Quadtree::clockwiseRotate()
{
  clockwiseRotateHelper(root);
  //reserved for 5.2
}

void Quadtree::clockwiseRotateHelper(QuadtreeNode* node)
{
  if (node == NULL || node->nwChild == NULL) return;
  QuadtreeNode* ne = node->nwChild;
  QuadtreeNode* se = node->neChild;
  QuadtreeNode* sw = node->seChild;
  QuadtreeNode* nw = node->swChild;
  node->nwChild = nw;
  node->neChild = ne;
  node->seChild = se;
  node->swChild = sw;
  clockwiseRotateHelper(node->nwChild);
  clockwiseRotateHelper(node->neChild);
  clockwiseRotateHelper(node->seChild);
  clockwiseRotateHelper(node->swChild);
}

void Quadtree::prune(int tolerance)
{
  pruneHelper(tolerance,root);
    // reserved for 5.2
}

void Quadtree::pruneHelper(int tolerance, QuadtreeNode* node)
{
  if (node == NULL || node->nwChild == NULL) return;
  // check whether it is prunable
  bool check = pruned(tolerance,node,node);
  // if it is prunable, then delete all leaves
  if (check)
  {
    clear(node->nwChild);
    node->nwChild = NULL;
    clear(node->neChild);
    node->neChild = NULL;
    clear(node->swChild);
    node->swChild = NULL;
    clear(node->seChild);
    node->seChild = NULL;
  }
  //recursively prune
  else
  {
  pruneHelper(tolerance,node->nwChild);
  pruneHelper(tolerance,node->neChild);
  pruneHelper(tolerance,node->swChild);
  pruneHelper(tolerance,node->seChild);
  }
}

bool Quadtree::pruned(int tolerance, QuadtreeNode* node, QuadtreeNode* subnode) const
{
  if (node == NULL || subnode == NULL) return false;
  bool p = true;
  // if it is leaf node
  if (subnode->nwChild == NULL)
  {
    int diff =(pow(node->element.red - subnode->element.red,2) +
              pow(node->element.green - subnode->element.green,2) +
              pow(node->element.blue - subnode->element.blue,2));
    p = (diff <= tolerance);
  }
  else
  {
    // recursively checking subnodes
    p = pruned(tolerance,node,subnode->nwChild) &&
        pruned(tolerance,node,subnode->neChild) &&
        pruned(tolerance,node,subnode->swChild) &&
        pruned(tolerance,node,subnode->seChild);
  }
  return p;
}

int Quadtree::pruneSize(int tolerance) const
{
  return prunesizeHelper(tolerance,root);
}

int Quadtree::prunesizeHelper(int tolerance, QuadtreeNode* node) const
{
  // if root is NULL, return 0
  if (node == NULL) return 0;
  bool check = pruned(tolerance,node,node);
  // every time when we delete all leaves, return 1
  if (check)
  {
    return 1;
  }
  else
  {
    // recursively calculate the size
    return prunesizeHelper(tolerance,node->neChild) + prunesizeHelper(tolerance,node->nwChild)
         + prunesizeHelper(tolerance,node->swChild) + prunesizeHelper(tolerance,node->seChild);
  }
}

int Quadtree::idealPrune(int numLeaves) const
{
  // if root is NULL, tolerance would be 0
  if (root == NULL) return 0;

  int max = pow(255,2) * 3;
  return binarySearch(numLeaves,0,max);
}

int Quadtree::binarySearch(int leaves, int left, int right) const
{
  int mid;
  if (right <= left)
    return left;
  mid = (left + right)/2;
  // go right
  if (pruneSize(mid) > leaves)
    return binarySearch(leaves,mid+1,right);
  // go left
  else  return binarySearch(leaves,left,mid);
}
