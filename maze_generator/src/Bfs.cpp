#include "Bfs.hpp"

Bfs::Bfs(Maze &maze, int startX, int startY, int endX, int endY)
    : maze_(maze), startX_(startX), startY_(startY), endX_(endX), endY_(endY) {
      };

bool Bfs::isVisited(Cell &to_check) const
{
    return visited_cell.find(to_check.getID()) != visited_cell.end();
}

map<int, PairInfo> &Bfs::initToMap(Cell &to_init)
{
    int cellID = to_init.getID();

    // {ID : (inf,-1)}
    pathInfo[cellID] = {INFINITY, -1};

    return pathInfo;
}

map<int, PairInfo> &Bfs::updateToMap(Cell &from, Cell &previous, int distance)
{
    int prev = previous.getID();
    int fromID = from.getID();

    if (distance < pathInfo[prev].first)
    {
        pathInfo[fromID] = {distance, prev};
    }

    return pathInfo;
}
map<int, PairInfo> &Bfs::updateToMap(Cell &from, int distance)
{
    int fromID = from.getID();

    pathInfo[fromID] = {distance, INF};

    return pathInfo;
}

void Bfs::initUnvisitedCell()
{
    int total = maze_.getWidth() * maze_.getHeight();

    for (int i = 0; i < total; i++)
    {
        unvisited_cell.insert(i);
    }
}
void Bfs::swapFromUnvisitied(Cell &cell)
{
    int id = cell.getID();
    visited_cell.insert(id);
    unvisited_cell.erase(id);
}

Cell &Bfs::backtrackToClosestCell()
{
    Cell *closest = nullptr;
    for (int id : visited_cell)
    {
        Cell &cell = maze_.getCellFromID(id);
        vector<Cell::Direction> directions =
            {Cell::UP, Cell::LEFT, Cell::DOWN, Cell::RIGHT};

        int x = cell.getX();
        int y = cell.getY();

        // can move
        for (Cell::Direction direction : directions)
        {
            if (!cell.hasWall(direction)) // we can use this path
            {

                int nx = 0, ny = 0;
                maze_.setX_Y_Neighbor(x, y, direction, nx, ny);

                Cell &neighbor = maze_.getCell(nx, ny);

                if (!isVisited(neighbor)) // the node must be unvisited
                {
                    closest = &cell;
                }
            }
        }
    }
    return *closest;
}

Cell &Bfs::findShortestPath(Cell &start)
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
            maze_.setX_Y_Neighbor(x, y, direction, nx, ny);

            Cell &neighbor = maze_.getCell(nx, ny);

            if (!isVisited(neighbor)) // the node must be unvisited
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

void Bfs::solve(Cell &start, Cell &end)
{

    cout << "Bfs cell taken :" << endl;
    initUnvisitedCell();

    while (start.getID() != end.getID())
    {
        cout << start.getID() << "-->";
        start = findShortestPath(start);
    }
    cout << start.getID() << endl;
}