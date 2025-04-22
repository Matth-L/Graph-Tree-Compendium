#include "KDnode.h"

KDnode::KDnode(std::vector<double> coordinates) : coordinates(coordinates), 
                                            left(nullptr), right(nullptr) {}

bool KDnode::isEqual(KDnode* other)
{
    return (coordinates == other->coordinates);
}

double KDnode::distanceSquared(KDnode* other)
{
    double dist = 0.f;
    for (size_t i = 0; i < coordinates.size(); ++i)
    {
        dist += (coordinates[i] - other->coordinates[i]) * 
                (coordinates[i] - other->coordinates[i]);
    }
    return dist;
}

KDnode* KDnode::minNode(KDnode* other1, KDnode* other2, KDnode* other3, int dim)
{
    KDnode* minNode = nullptr;

    // Compare other1 and other2
    if (other1 != nullptr && (minNode == nullptr || 
        other1->coordinates[dim] < minNode->coordinates[dim]))
    {
        minNode = other1;
    }

    if (other2 != nullptr && (minNode == nullptr || 
        other2->coordinates[dim] < minNode->coordinates[dim]))
    {
        minNode = other2;
    }

    // Compare the result with other3
    if (other3 != nullptr && (minNode == nullptr || 
        other3->coordinates[dim] < minNode->coordinates[dim]))
    {
        minNode = other3;
    }

    return minNode;
}

void KDnode::printNode()
{
    std::cout << "(";
    for (size_t i = 0; i < coordinates.size(); ++i)
    {
        std::cout << coordinates[i];
        if (i != coordinates.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << ")";
}