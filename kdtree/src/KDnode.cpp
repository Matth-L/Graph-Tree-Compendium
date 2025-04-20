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
    std::cout << ")" << std::endl;
}