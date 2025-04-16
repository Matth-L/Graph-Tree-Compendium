#include "Maze.hpp"
#include "Cell.hpp"
#include <set>
#include <map>
#include <unordered_map>
#include <iostream>
#include <array>

using pair_info = std::pair<int, int>;
class Dijkstra
{
public:
    Dijkstra(Maze &maze) : maze(maze) {}
    /**********************************************
     * @brief Use dijkstra algorithm to find the shortest path from a
     * cell to another
     *
     * @param start
     * @param end
     ***********************************************/
    Cell &findShortestPath(Cell &start, Cell &end);

    /**********************************************
     * @brief Calls recursively findShortespath until start = end
     *
     * @param start
     * @param end
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
    bool is_visited(Cell &to_check) const;

    map<int, pair_info> &initToMap(Cell &to_init);

    /**********************************************
     * @brief updates the cell to hte map with distance and value
     *
     * @param from
     * @param to
     * @param distance
     * @return map<int, pair_info>&
     ***********************************************/
    map<int, pair_info> &updateToMap(Cell &from, Cell &to, int distance);
    map<int, pair_info> &updateToMap(Cell &from, int distance);

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
    Maze &maze;

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
    map<int, pair_info> pathInfo;
};