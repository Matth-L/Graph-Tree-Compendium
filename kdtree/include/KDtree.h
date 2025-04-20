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
    KDtree(vector<KDnode>* points, int dim);

    KDnode* findNearestNeighbor(KDnode* target);
    KDnode* nearestNeighborAuxiliary(KDnode* current, KDnode* target, int depth);

    void add(KDnode* node);
    KDnode* addAuxiliary(KDnode* current, KDnode* node, int depth);

    void remove(KDnode* node);

    bool search(KDnode* node);
    bool searchAuxiliary(KDnode* current, KDnode* target, int depth);

    int getDimension() { return dimension; }

    void printTree() { printTreeAuxiliary("", root, false, true); }
    void printTreeAuxiliary(const string& prefix, const KDnode* node, bool isLeft, bool isRoot);
};

#endif