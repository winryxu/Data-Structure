/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
      Quadtree();
      Quadtree(PNG const &source, int resolution);
      Quadtree(Quadtree const &other);
      ~Quadtree();
      Quadtree operator= (Quadtree const &other);
      void buildTree(PNG const &source, int resolution);
      RGBAPixel getPixel(int x, int y) const;
      PNG decompress() const;
      void clockwiseRotate();
      void prune(int tolerance);
      int pruneSize(int tolerance) const;
      int idealPrune(int numLeaves) const;
  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */
        QuadtreeNode();
        QuadtreeNode(RGBAPixel elem);
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */

    int size;

    /*helper functions*/
    void clear(QuadtreeNode*& root);
    QuadtreeNode* buildTreeHelper(PNG const &source, int x,int y, int resolution);
    void copy(QuadtreeNode* const &other, QuadtreeNode* &q);
    void copy(Quadtree const& other);
    void decompressHelper(PNG &output, QuadtreeNode* root, int x, int y, int width) const;
    RGBAPixel getPixelHelper(int x, int y, QuadtreeNode* root, int size) const;
    void clockwiseRotateHelper(QuadtreeNode* node);
    void pruneHelper(int tolerance, QuadtreeNode* node);
    bool pruned(int tolerance, QuadtreeNode* node, QuadtreeNode* subnode) const;
    int prunesizeHelper(int tolerance, QuadtreeNode* node) const;
    int binarySearch(int leaves, int left, int right) const;

/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
