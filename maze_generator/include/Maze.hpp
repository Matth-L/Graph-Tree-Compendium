/**
 * @file maze.h
 * @Matth-L
 */

#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <stack>
#include <random>
#include <ctime>
#include <random>

#include "Cell.hpp"

using namespace std;

class Maze
{
public:
    /**********************************************
     * @brief Construct a new Maze
     *
     * @param width of the maze
     * @param height of the maze
     ***********************************************/
    Maze(int width, int height);

    /**********************************************
     *  @brief generate the maze using the grow tree algorithm
     *
     ***********************************************/
    void generate();

    /**********************************************
     * @brief print the maze
     *
     ***********************************************/
    void print() const;

    /**********************************************
     * @brief Choose randomly the first cell in the maze, the id is 1
     *
     * @return Cell& the new cell
     ***********************************************/
    Cell &pick_starter_position();

    /**********************************************
     * @brief Choose randomly the next cell using the growth algorithm
     *
     * @return Cell& the new chosen cell using the previous one
     ***********************************************/
    Cell &pick_new_cell();

    /**********************************************
     * @brief break the wall from one cell to another
     *
     * @param current the cell where we actually are
     * @param next the next cell to go to
     * @param direction
     ***********************************************/
    void break_wall(Cell &current, Cell &next, Cell::Direction direction);

    /**********************************************
     * @brief Get the neighbor coordinate, it's a grid so +1, -1 will be enough
     *
     * @param x the current x
     * @param y the current y
     * @param direction the direction of the next cell to get
     * @return pair<int, int>
     ***********************************************/
    pair<int, int> get_neighbor_coordinate(int x, int y, Cell::Direction direction);

    /**********************************************
     * @brief Checks if the coordinate are in the maze or outside
     *
     * @param x coodinates
     * @param y coordinates
     * @return true if it's in the maze
     * @return false otherwise
     ***********************************************/
    bool is_within_bounds(int x, int y) const;

    /**********************************************
     * @brief get a positive random value
     *
     * @return int
     ***********************************************/
    int getRNG();

    /**********************************************
     * @brief Add a cell to a stack, put vistied to true, increment the id
     *
     ***********************************************/
    void addToStack(Cell &cell, int previous_id);

private:
    int width_;
    int height_;
    vector<vector<Cell>> grid_;
    stack<Cell *> list_of_cell_;

    // random number generation
    static inline mt19937 sGenerator_{random_device{}()};
};

#endif // MAZE_H
