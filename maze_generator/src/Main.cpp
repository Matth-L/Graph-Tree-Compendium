#include "Maze.hpp"
#include "AStar.hpp"
#include "Dijkstra.hpp"
#include <iostream>

using namespace std;

int main()
{
    Maze maze(8, 8);
    maze.generate(8, 8);
    Cell start = maze.getCellFromID(5);
    Cell end = maze.getCellFromID(25);

    Dijkstra dijkstra(maze, start.getX(), start.getY(), end.getX(), end.getY());

    AStar astar(maze, start.getX(), start.getY(), end.getX(), end.getY());

    dijkstra.solve(start, end);
    astar.solveAndPrint();

    return 0;
}
