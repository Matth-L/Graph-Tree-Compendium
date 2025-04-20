#ifndef KDNODE_H
#define KDNODE_H

#include <vector>
#include <iostream>

using namespace std;

class KDnode
{

public:
    KDnode() : left(nullptr), right(nullptr) {}
    KDnode(vector<double> coordinates);

    vector<double> coordinates;
    KDnode* left;
    KDnode* right;


    bool isEqual(KDnode* other);
    double distanceSquared(KDnode* other);

    void printNode();
};

#endif