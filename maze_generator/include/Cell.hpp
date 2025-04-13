/**********************************************
 * @file cell.h
 * @author Matth-L
 ***********************************************/

#ifndef CELL_H
#define CELL_H

class Cell
{
private:
    bool visited_;
    bool walls_[4];

public:
    enum Direction
    {
        UP = 0,
        LEFT = 1,
        DOWN = 2,
        RIGHT = 3
    };

    Cell();

    bool isVisited() const;

    void setVisited(bool visited);

    bool hasWall(char direction) const;

    void removeWall(char direction);
};

#endif // CELL_H
