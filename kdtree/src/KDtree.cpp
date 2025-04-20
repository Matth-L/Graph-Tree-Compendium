#include "KDtree.h"

KDtree::KDtree(vector<KDnode>* points, int dim)
{
    dimension = dim;
    root = nullptr;
    
    for (auto point : *points)
    {
        add(&point);
    }
}

KDnode* KDtree::findNearestNeighbor(KDnode* target)
{
    return nearestNeighborAuxiliary(root, target, 0);
}

KDnode* KDtree::nearestNeighborAuxiliary(KDnode* current, KDnode* target, int depth)
{
    // Base case: if the current node is null, return null
    if (current == nullptr) return nullptr;

    if (current->isEqual(target)) return current;

    int cd = depth % dimension;

    KDnode* nextBranch = current->right;
    KDnode* otherBranch = current->left;

    if (target->coordinates.at(cd) < current->coordinates.at(cd))
    {
        nextBranch = current->left;
        otherBranch = current->right;
    }

    KDnode* tmp = nearestNeighborAuxiliary(nextBranch, target, depth + 1);
    KDnode* best = tmp;
    if (tmp == nullptr || tmp->distanceSquared(target) > current->distanceSquared(target))
    {
        best = current;
    }

    double dist = target->coordinates.at(cd) - current->coordinates.at(cd);
    if (dist * dist < best->distanceSquared(target))
    {
        tmp = nearestNeighborAuxiliary(otherBranch, target, depth + 1);
        if (tmp != nullptr && tmp->distanceSquared(target) < best->distanceSquared(target))
        {
            best = tmp;
        }
    }

    return best;
}


KDnode* KDtree::addAuxiliary(KDnode* current, KDnode* node, int depth)
{
    // Base case: if the current node is null, insert the new node here
    if (current == nullptr)
    {
        return node;
    }

    // Compare the new node's coordinate with the current node's coordinate
    int cd = depth % dimension;

    if (node->coordinates.at(cd) < current->coordinates.at(cd))
    {
        current->left = addAuxiliary(current->left, node, depth + 1);
    }
    else
    {
        current->right = addAuxiliary(current->right, node, depth + 1);
    }
    

    return current;
}

void KDtree::add(KDnode* node)
{
    if (root == nullptr)
    {
        root = node;
        return;
    }
    addAuxiliary(root, node, 0);
}

void KDtree::remove(KDnode* node)
{
    // Implement remove logic here
}

bool KDtree::searchAuxiliary(KDnode* current, KDnode* target, int depth)
{
    // Base case: if the current node is null, return false
    // This means we have reached a leaf node without finding the target
    if (current == nullptr) return false;

    // Check if the current node is equal to the target node
    if (current->isEqual(target)) return true;

    // Compare the target's coordinate with the current node's coordinate
    int cd = depth % dimension;

    if (target->coordinates.at(cd) < current->coordinates.at(cd))
    {
        return searchAuxiliary(current->left, target, depth + 1);
    }
    return searchAuxiliary(current->right, target, depth + 1);
}

bool KDtree::search(KDnode* node)
{
    return searchAuxiliary(root, node, 0);
}

void KDtree::printTreeAuxiliary(const string& prefix, const KDnode* node, bool isLeft, bool isRoot)
{
    if( node != nullptr )
    {
        if (isRoot) cout << "─────";
        else 
        {
            cout << prefix << (isLeft ? "L├────" : "R└───");
        }

        // print the value of the node
        for (int i = 0; i < dimension; i++)
        {
            cout << node->coordinates.at(i);
            if (i < dimension - 1) cout << ",";
        }
        cout << endl;

        // enter the next tree level - left and right branch
        printTreeAuxiliary( prefix + (isLeft ? " │   " : "    "), node->left, true, false);
        printTreeAuxiliary( prefix + (isLeft ? " │   " : "    "), node->right, false, false);
    }
}
