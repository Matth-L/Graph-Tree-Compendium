#include "Cell.hpp"
#include "Maze.hpp"
#include "Dijkstra.hpp"
#include <random>
#include <iostream>

int main()
{
    Maze a;
    a.generate(8, 8);
    Cell start = a.getCellFromID(0);
    Cell end = a.getCellFromID(62);
    Dijkstra b(a);
    b.solve(start, end);
    b.printMap();
}