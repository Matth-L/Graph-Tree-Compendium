#include "Maze.hpp"
#include "Cell.hpp"
#include <set>
#include <map>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using PairInfo = std::pair<int, int>;
using Coordinate = pair<int, int>;

class Bfs
{

public:
    Bfs(Maze &maze, int startX, int startY, int endX, int endY);

    /**********************************************
     * @brief Use Bfs algorithm to find the shortest path from a
     * cell to another
     *
     * @param start
     * @param end
     ***********************************************/
    Cell &findShortestPath(Cell &start);

    /**********************************************
     * @brief Calls recursively findShortespath until start = end
     *
     * @param start
     * @param end
     * @return the paht vector
     ***********************************************/
    void solve(Cell &start, Cell &end);

    /**********************************************
     * @brief prints the path info map with previous node, visited state,
     * shortest distance and so on
     ***********************************************/
    void printMap() const;

    /**********************************************
     * @brief initialise all the cell to unvisited
     * -> adds it to the set
     *
     ***********************************************/
    void initUnvisitedCell();

    /**********************************************
     * @brief insert in visited, erase from unvisited
     *
     * @param c
     ***********************************************/
    void swapFromUnvisitied(Cell &c);

    /**********************************************
     * @brief check if a cell is in the visited set
     *
     * @param to_check
     * @return true
     * @return false
     ***********************************************/
    bool isVisited(Cell &to_check) const;

    /**********************************************
     * @brief init the map
     *
     * @param to_init
     * @return map<int, PairInfo> an initialized map
     ***********************************************/
    map<int, PairInfo> &initToMap(Cell &to_init);

    /**********************************************
     * @brief updates the cell to hte map with distance and value
     *
     * @param from
     * @param to
     * @param distance
     * @return map<int, PairInfo>&
     ***********************************************/
    map<int, PairInfo> &updateToMap(Cell &from, Cell &to, int distance);
    map<int, PairInfo> &updateToMap(Cell &from, int distance);

    /**********************************************
     * @brief backtrack to the closest cell if we cannot move forward
     *
     * @return Cell&
     ***********************************************/
    Cell &backtrackToClosestCell();

    /**********************************************
     * @brief the list of visited node, if we cant move forward, we will take
     * another node from this list
     *
     ***********************************************/
    vector<Cell> visited_list; // to backtrack if there is nowhere to go

    Maze &setMaze(Maze to_add);

private:
    Maze &maze_;
    int startX_;
    int startY_;
    int endX_;
    int endY_;

    unordered_map<int, std::pair<int, int>> idToCoordinates_; // Map IDs to coordinates

    /**********************************************
     * @brief A set containing the visited cell
     *
     ***********************************************/
    set<int> visited_cell;

    /**********************************************
     * @brief A set containing the unvisited cell
     *
     ***********************************************/
    set<int> unvisited_cell;

    /**********************************************
     * @brief {cell_id : {shortest_distance,previous_cell}
     *
     ***********************************************/
    map<int, PairInfo> pathInfo;
};