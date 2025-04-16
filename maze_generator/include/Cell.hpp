/**********************************************
 * @file cell.h
 * @author Matth-L
 ***********************************************/

#ifndef CELL_H
#define CELL_H

#include <array>

using namespace std;

class Cell
{
private:
    bool is_visited_;
    array<bool, 4> walls_; // {UP, LEFT, DOWN, RIGHT}
    int cell_id_;
    int coordinate_x;
    int coordinate_y;

    // a cell could be "heavier" than another, for example if its a swamp
    int weight_ = 1;

public:
    enum Direction
    {
        UP = 0,
        LEFT = 1,
        DOWN = 2,
        RIGHT = 3
    };

    /**********************************************
     * @brief Construct a new Cell object
     * It also inits the coordinates of the cell ,
     *  UP = 0,
     *  LEFT = 1,
     *  DOWN = 2,
     *  RIGHT = 3
     *
     ***********************************************/
    Cell() : is_visited_(false), walls_{{true, true, true, true}} {}

    /**********************************************
     * @brief check if the cell is already used in the maze
     *
     * @return true
     * @return false
     ***********************************************/
    bool isVisited() const;

    /**********************************************
     * @brief Set the Visited object
     *
     * @param initialized
     ***********************************************/
    void setVisited(bool initialized);

    /**********************************************
     * @brief Checks if there is a wall in this direction
     *
     * @param direction
     * @return true
     * @return false
     ***********************************************/
    bool hasWall(Direction direction) const;

    /**********************************************
     * @brief Remove the wall in this direction
     *
     * @param direction
     ***********************************************/
    void removeWall(Direction direction);

    /**********************************************
     * @brief Get the total number of wall from a cell
     *
     * @return int the number of wall
     ***********************************************/
    int numberOfWall();

    /**********************************************
     * @brief Set the Walls
     *
     * @param walls an array of boolean
     ***********************************************/
    void setWalls(array<bool, 4> &walls);

    /**********************************************
     * @brief Get the Walls
     *
     * @return array<bool, 4>
     ***********************************************/
    array<bool, 4> getWalls() const;

    /**********************************************
     * @brief get the id of the cell
     *
     * @return int the id
     ***********************************************/
    int getID() const;

    /**********************************************
     * @brief set the id of the cell
     *
     * @param id the id
     ***********************************************/
    void setID(int id);

    /**********************************************
     * @brief Set the Coordinates
     *
     * @param x
     * @param y
     ***********************************************/
    void setCoordinates(int x, int y);

    /**********************************************
     * @brief get the X value of the grid
     *
     * @return int
     ***********************************************/
    int getX() const;

    /**********************************************
     * @brief get the Y value of the grid
     *
     * @return int
     ***********************************************/
    int getY() const;

    int getWeight() const;
};

#endif // CELL_H
