#include "KDtree.h"

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

KDnode* KDtree::findNearestNeighbor(KDnode* target)
{
    return nearestNeighborAuxiliary(root, target, 0);
}

KDnode* KDtree::findMinDimAuxiliary(KDnode* current, int dim, int depth)
{
    if (current == nullptr) return nullptr;

    // Compare the current node's coordinate with the target coordinate
    int cd = depth % dimension;

    if (cd == dim)
    {
        // If the current dimension is the same as the target dimension,
        // go left first
        if (current->left == nullptr) return current;
        return findMinDimAuxiliary(current->left, dim, depth + 1);
    }

    // If the current dimension is not the same as the target dimension,
    // check both branches
    return KDnode::minNode(
        current,
        findMinDimAuxiliary(current->left, dim, depth + 1),
        findMinDimAuxiliary(current->right, dim, depth + 1),
        dim);
}


KDnode* KDtree::findMinDim(KDnode* node, int dim)
{
    return findMinDimAuxiliary(node, dim, 0);
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

KDnode* KDtree::removeAuxiliary(KDnode* current, KDnode* node, int depth)
{
    if ( current == nullptr ) return nullptr;

    int cd = depth % dimension;

    if ( current->isEqual(node) )
    {
        // Node found, remove it
        if ( current->right != nullptr )
        {
            KDnode* minNode = findMinDim(current->right, cd);
            // Copy the coordinates of the minimum node to the current node
            current->coordinates = minNode->coordinates;
            // Remove the minimum node from the right subtree
            current->right = removeAuxiliary(current->right, minNode, depth + 1);
        }
        else if ( current->left != nullptr )
        {
            KDnode* minNode = findMinDim(current->left, cd);
            current->coordinates = minNode->coordinates;
            current->right = removeAuxiliary(current->left, minNode, depth + 1);
            current->left = nullptr; // Set left to null since we moved the node
        }
        else // Node to delete is a leaf
        {
            return nullptr;
        }
        return current;
    }

    if ( node->coordinates.at(cd) < current->coordinates.at(cd) )
    {
        current->left = removeAuxiliary(current->left, node, depth + 1);
    }
    else
    {
        current->right = removeAuxiliary(current->right, node, depth + 1);
    }
    return current;
}

void KDtree::remove(KDnode* node)
{
    removeAuxiliary(root, node, 0);
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
