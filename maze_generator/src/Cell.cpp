#include "Cell.hpp"

Cell::Cell() : visited_(false)
{
    walls_[4] = {true};
}

bool Cell::isVisited() const
{
    return visited_;
}

void Cell::setVisited(bool visited)
{
    visited_ = visited;
}

bool Cell::hasWall(char direction) const
{
    switch (direction)
    {
    case 'U':
        return walls_[UP];
    case 'L':
        return walls_[LEFT];
    case 'D':
        return walls_[DOWN];
    case 'R':
        return walls_[RIGHT];
    default:
        return false;
    }
}

// Supprime un mur dans une direction donnée
void Cell::removeWall(char direction)
{
    switch (direction)
    {
    case 'U':
        walls_[UP] = false;
        break;
    case 'L':
        walls_[LEFT] = false;
        break;
    case 'D':
        walls_[DOWN] = false;
        break;
    case 'R':
        walls_[RIGHT] = false;
        break;
    }
}
