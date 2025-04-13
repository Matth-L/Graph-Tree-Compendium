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
#include "Cell.hpp"

using namespace std;

class Maze
{
public:
    Maze(int width, int height);

    void generate();

    void print() const;

private:
    int width_;
    int height_;
    vector<vector<Cell>> grid_;
    stack<pair<int, int>> frontier_;
};

#endif // MAZE_H
