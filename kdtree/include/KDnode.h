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

    /**********************************************
    * @brief Check if the node is equal to another node
    *
    * @param other the other node to compare
    * @return bool true if the node is equal to the other node
    ***********************************************/
    bool isEqual(KDnode* other);

    /**********************************************
    * @brief Check if the node is less than another node
    *
    * @param other the other node to compare
    * @return bool true if the node is less than the other node
    ***********************************************/
    double distanceSquared(KDnode* other);

    /**********************************************
    * @brief Find the minimum node in the given dimension
    *
    * @param other1 the first node to compare
    * @param other2 the second node to compare
    * @param other3 the third node to compare
    * @param dim the dimension to find the minimum node
    * @return KDnode* the minimum node in the given dimension
    ***********************************************/
    static KDnode* minNode(KDnode* other1, KDnode* other2, KDnode* other3, int dim);

    void printNode();
};

#endif