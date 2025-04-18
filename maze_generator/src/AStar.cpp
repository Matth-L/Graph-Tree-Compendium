#include "AStar.hpp"

AStar::AStar(Maze &maze, int startX, int startY, int endX, int endY)
    : maze_(maze), startX_(startX), startY_(startY), endX_(endX), endY_(endY),
      width_(maze.getWidth()), height_(maze.getHeight()) {}

int AStar::heuristic(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

bool AStar::isValid(int x, int y)
{
    return maze_.is_within_bounds(x, y);
}

AStar::Coordinate AStar::getNeighborCoordinate(int x, int y, Cell::Direction direction)
{
    return maze_.get_neighbor_coordinate(x, y, direction);
}

void AStar::initializeMaps(CostMap &cost, ParentMap &parent)
{
    for (int i = 0; i < height_; ++i)
    {
        for (int j = 0; j < width_; ++j)
        {
            cost[j][i] = INF;
        }
    }
    cost[startX_][startY_] = 0;
    parent.clear();
}

void AStar::processCell(int x, int y, PriorityQueue &pq, CostMap &cost, ParentMap &parent)
{
    vector<Cell::Direction> directions = {Cell::UP, Cell::LEFT, Cell::DOWN, Cell::RIGHT};

    for (const auto &dir : directions)
    {
        Coordinate neighbor = getNeighborCoordinate(x, y, dir);
        int nx = neighbor.first;
        int ny = neighbor.second;

        // we can reach it
        if (isValid(nx, ny) && !maze_.getCell(x, y).hasWall(dir))
        {
            int newCost = cost[x][y] + 1;

            // uddate if cost lower
            if (newCost < cost[nx][ny])
            {
                cost[nx][ny] = newCost;
                parent[nx * height_ + ny] = {x, y};
                pq.push({newCost + heuristic(nx, ny, endX_, endY_), {nx, ny}});
            }
        }
    }
}

vector<AStar::Coordinate> AStar::reconstructPath(int x, int y, ParentMap &parent)
{
    vector<Coordinate> path;

    // Trace back from the end cell to the start cell
    while (!(x == startX_ && y == startY_))
    {
        path.push_back({x, y});
        auto it = parent.find(x * height_ + y);
        if (it == parent.end())
            break;
        int px = it->second.first;
        int py = it->second.second;
        x = px;
        y = py;
    }
    path.push_back({startX_, startY_});
    reverse(path.begin(), path.end());
    return path;
}

vector<AStar::Coordinate> AStar::findPath()
{
    // comparison funcion for the priority queue
    auto compare = [](const pair<int, Coordinate> &a, const pair<int, Coordinate> &b)
    {
        return a.first > b.first;
    };
    PriorityQueue pq(compare);

    CostMap cost;
    ParentMap parent;
    initializeMaps(cost, parent);

    // push init cell
    pq.push({0, {startX_, startY_}});

    // Process cells until the priority queue is empty
    while (!pq.empty())
    {
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        // done, so reconstruct the path
        if (x == endX_ && y == endY_)
        {
            return reconstructPath(x, y, parent);
        }

        // explore neighbors
        processCell(x, y, pq, cost, parent);
    }

    cout << "No path found, all cells processed.\n";
    return {};
}

void AStar::solveAndPrint()
{
    cout << "a star path found : " << endl;
    vector<Coordinate> path = findPath();
    // Print the path
    if (!path.empty())
    {
        for (const auto &p : path)
        {
            cout << "(" << maze_.getCell(p.first, p.second).getID() << ") ";
        }
        cout << endl;
    }
    else
    {
        cout << "No path found.\n";
    }
}
