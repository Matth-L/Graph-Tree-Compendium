#include "Dijkstra.hpp"

bool Dijkstra::is_visited(Cell &to_check) const
{
    return visited_cell.find(to_check.getID()) != visited_cell.end();
}

map<int, pair_info> &Dijkstra::initToMap(Cell &to_init)
{
    int cellID = to_init.getID();

    // {ID : (inf,-1)}
    pathInfo[cellID] = {INFINITY, -1};

    return pathInfo;
}

map<int, pair_info> &Dijkstra::updateToMap(Cell &from, Cell &previous, int distance)
{
    int prev = previous.getID();
    int fromID = from.getID();

    if (distance < pathInfo[prev].first)
    {
        pathInfo[fromID] = {distance, prev};
    }

    return pathInfo;
}
map<int, pair_info> &Dijkstra::updateToMap(Cell &from, int distance)
{
    int fromID = from.getID();

    pathInfo[fromID] = {distance, INF};

    return pathInfo;
}

void Dijkstra::initUnvisitedCell()
{
    int total = maze.getWidth() * maze.getHeight();

    for (int i = 0; i < total; i++)
    {
        unvisited_cell.insert(i);
    }
}
void Dijkstra::swapFromUnvisitied(Cell &cell)
{
    int id = cell.getID();
    visited_cell.insert(id);
    unvisited_cell.erase(id);
}

Cell &Dijkstra::backtrackToClosestCell()
{
    Cell *closest = nullptr;
    for (int id : visited_cell)
    {
        Cell &cell = maze.getCellFromID(id);
        vector<Cell::Direction> directions =
            {Cell::UP, Cell::LEFT, Cell::DOWN, Cell::RIGHT};

        int minimal_weight = INF;
        int x = cell.getX();
        int y = cell.getY();

        // can move
        for (Cell::Direction direction : directions)
        {
            if (!cell.hasWall(direction)) // we can use this path
            {

                int nx = 0, ny = 0;
                maze.setX_Y_Neighbor(x, y, direction, nx, ny);

                Cell &neighbor = maze.getCell(nx, ny);

                if (!is_visited(neighbor)) // the node must be unvisited
                {
                    closest = &cell;
                }
            }
        }
    }
    return *closest;
}

Cell &Dijkstra::findShortestPath(Cell &start, Cell &end)
{
    updateToMap(start, 0);

    if (unvisited_cell.empty())
    {
        return start;
    }

    // find the minimal distance, a.k.a weight
    vector<Cell::Direction> directions =
        {Cell::UP, Cell::LEFT, Cell::DOWN, Cell::RIGHT};

    int minimal_weight = INF;
    int x = start.getX();
    int y = start.getY();
    Cell *chosen_cell = nullptr;

    for (Cell::Direction direction : directions)
    {
        if (!start.hasWall(direction)) // we can use this path
        {
            int nx = 0, ny = 0;
            maze.setX_Y_Neighbor(x, y, direction, nx, ny);

            Cell &neighbor = maze.getCell(nx, ny);

            if (!is_visited(neighbor)) // the node must be unvisited
            {
                int weight = neighbor.getWeight();

                // we choose the minimal distance
                if (weight < minimal_weight)
                {
                    minimal_weight = neighbor.getWeight();

                    // update shortest distance, if new distance is shorter than old distance
                    updateToMap(neighbor, start, weight);
                    // we will move to the latest node with the minimal weight
                    chosen_cell = &neighbor;
                }
            }
        }
    }

    // mark current node as visited
    swapFromUnvisitied(start);

    if (chosen_cell == nullptr)
    {
        return backtrackToClosestCell();
    }

    return *chosen_cell;
}

void Dijkstra::solve(Cell &start, Cell &end)
{
    initUnvisitedCell();

    while (start.getID() != end.getID())
    {
        start = findShortestPath(start, end);
    }
}

void Dijkstra::printMap() const
{
    int width = maze.getWidth();
    int height = maze.getHeight();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Cell cell = maze.getCell(x, y);
            int cellID = cell.getID();

            // Print cell information
            std::cout << "Cell (" << x << ", " << y << "): ";

            // Check if the cell is visited
            if (is_visited(cell))
            {
                std::cout << "Visited, ";
            }
            else
            {
                std::cout << "Unvisited, ";
            }

            // Print shortest path information
            auto it = pathInfo.find(cellID);
            if (it != pathInfo.end())
            {
                std::cout << "Distance: " << it->second.first << ", ";
                std::cout << "Previous: " << it->second.second;
            }

            std::cout << std::endl;
        }
        std::cout << std::endl; // New line for better readability
    }
}
