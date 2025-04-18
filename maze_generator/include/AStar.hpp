#ifndef ASTAR_HPP
#define ASTAR_HPP

#include "Maze.hpp"
#include "Cell.hpp"
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <functional>

using namespace std;

class AStar
{

    using Path = vector<pair<int, int>>;

    /**********************************************
     * @brief the coordinates of the cell (x,y)
     *
     ***********************************************/
    using Coordinate = pair<int, int>;

    /**********************************************
     * @brief  the cost to reach each cell.
     *
     ***********************************************/
    using CostMap = unordered_map<int, unordered_map<int, int>>;

    /**********************************************
     * @brief a map storing the parent of each cell for path reconstruction.
     *
     ***********************************************/
    using ParentMap = unordered_map<int, Coordinate>;

    /**********************************************
     * @brief the priority queue to explore other cells
     *
     ***********************************************/
    using PriorityQueue = priority_queue<pair<int, Coordinate>,
                                         vector<pair<int, Coordinate>>,
                                         function<bool(const pair<int, Coordinate> &,
                                                       const pair<int, Coordinate> &)>>;

public:
    AStar(Maze &maze, int startX, int startY, int endX, int endY);

    /**********************************************
     * @brief Find the shortest path from the start
     * to the end coordinates using the A* algorithm.
     *
     * @return Vector of coordinates representing the path from start to end.
     ***********************************************/
    Path findPath();

    /**********************************************
     * @brief solve the maze using a* and prints the result
     * @note uses findPath() and simply print ...
     ***********************************************/
    void solveAndPrint();

private:
    Maze &maze_;
    int startX_;
    int startY_;
    int endX_;
    int endY_;
    int width_;
    int height_;

    /**********************************************
     * @brief Manhattan distance between 2 points
     *
     * @return int
     ***********************************************/
    int heuristic(int x1, int y1, int x2, int y2);

    /**********************************************
     * @brief Check if a cell is within the valid bounds of the maze
     * @note uses Maze::is_within_bound
     ***********************************************/
    bool isValid(int x, int y);

    /**********************************************
     * @brief Get the Neighbor Coordinate object
     * @note uses Maze::is_within_bound
     ***********************************************/
    Coordinate getNeighborCoordinate(int x, int y, Cell::Direction direction);

    /**********************************************
     * @brief Initialiaze the unordered map of cost and parent
     *
     * @param cost
     * @param parent
     ***********************************************/
    void initializeMaps(CostMap &cost, ParentMap &parent);

    /**********************************************
     * @brief process a cell and update teh prioriity queue
     *
     ***********************************************/
    void processCell(int x, int y, PriorityQueue &pq, CostMap &cost, ParentMap &parent);

    /**********************************************
     * @brief Reconstruct the path from the end to the start
     *
     * @return vector<Coordinate> the path
     ***********************************************/
    vector<Coordinate> reconstructPath(int x, int y, ParentMap &parent);
};

#endif // ASTAR_HPP
