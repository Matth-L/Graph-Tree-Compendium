#include "Cell.hpp"

bool Cell::isVisited() const
{
    return is_visited_;
}

void Cell::setVisited(bool visited)
{
    is_visited_ = visited;
}

bool Cell::hasWall(Direction x) const
{
    return walls_[x];
}

void Cell::removeWall(Direction x)
{
    walls_[x] = false;
}

void Cell::setWalls(array<bool, 4> &walls)
{
    walls_ = walls;
}

array<bool, 4> Cell::getWalls() const
{
    return walls_;
}

int Cell::getID() const
{
    return cell_id_;
}

void Cell::setID(int id)
{
    cell_id_ = id;
}

int Cell::numberOfWall()
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        walls_[i] ? count++ : count;
    }
    return count;
}

void Cell::setCoordinates(int x, int y)
{
    coordinate_x = x;
    coordinate_y = y;
}
int Cell::getX() const
{
    return coordinate_x;
}

int Cell::getY() const
{
    return coordinate_y;
}