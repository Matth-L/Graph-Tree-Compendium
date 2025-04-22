#ifndef KDTREE_H
#define KDTREE_H

#include "KDnode.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class KDtree
{

public:
    KDnode* root;

    int dimension;

    
    KDtree(int dim) : root(nullptr), dimension(dim) {}
    KDtree(KDnode* root) : root(root), dimension(root->coordinates.size()) {}

     /**********************************************
    * @brief Find the nearest neighbor of the target node
    *
    * @param target the target node to find the nearest neighbor
    * @return KDnode* the nearest neighbor node
    * @note This function uses the Euclidean distance to find the nearest neighbor
    * @note The function will return the first node found if there are multiple nearest neighbors
    * @return KDnode* the nearest neighbor node
    ***********************************************/
    KDnode* findNearestNeighbor(KDnode* target);
    KDnode* nearestNeighborAuxiliary(KDnode* current, KDnode* target, int depth);

    /**********************************************
    * @brief Find the minimum node in the given dimension
    *
    * @param node the root of the tree
    * @param dim the dimension to find the minimum node
    * @return KDnode* the minimum node in the given dimension
    ***********************************************/
    KDnode* findMinDim(KDnode* node, int dim);
    KDnode* findMinDimAuxiliary(KDnode* current, int dim, int depth);

     /**********************************************
    * @brief Add a node to the tree
    *
    * @param node the node to add
    * @return void
    ***********************************************/
    void add(KDnode* node);
    KDnode* addAuxiliary(KDnode* current, KDnode* node, int depth);

    /**********************************************
    * @brief Remove a node from the tree
    *
    * @param node the node to remove
    * @return void
    ***********************************************/
    void remove(KDnode* node);
    KDnode* removeAuxiliary(KDnode* current, KDnode* node, int depth);

    /**********************************************
    * @brief Search for a node in the tree
    *
    * @param node the node to search
    * @return bool true if the node is found, false otherwise
    ***********************************************/
    bool search(KDnode* node);
    bool searchAuxiliary(KDnode* current, KDnode* target, int depth);

    int getDimension() { return dimension; }

    /**********************************************
    * @brief Print the tree
    *
    * @return void
    ***********************************************/
    void printTree() { printTreeAuxiliary("", root, false, true); }
    void printTreeAuxiliary(const string& prefix, const KDnode* node, bool isLeft, bool isRoot);
};

#endif