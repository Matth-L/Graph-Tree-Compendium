#include "Maze.hpp"
#include <iostream>
#include <algorithm>
#include <iomanip>

Maze::Maze()
{
}

Cell &Maze::getCell(int x, int y)
{
    return grid_[y][x];
}

Maze::Maze(int w, int h) : width_(w), height_(h), grid_(h, vector<Cell>(w))
{
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            grid_[i][j].setCoordinates(j, i);
        }
    }
}

int Maze::getRNG()
{
    return abs((int)sGenerator_());
}

void Maze::print() const
{
    for (int y = 0; y < height_; ++y)
    {
        for (int x = 0; x < width_; ++x)
        {
            const Cell &cell = grid_[y][x];
            const array<bool, 4> &walls = cell.getWalls();

            // top wall
            cout << (walls[Cell::UP] ? "+----" : "+    ");
        }
        // EOL top walls
        cout << "+\n";

        // the left wall and cell itself
        for (int x = 0; x < width_; ++x)
        {
            const Cell &cell = grid_[y][x];
            const array<bool, 4> &walls = cell.getWalls();
            cout << (walls[Cell::LEFT] ? "| " : "  ");
            cout << setw(2) << cell.getID() << " ";
        }
        // EOL left walls and cells
        cout << "|\n";
    }

    // bottom wall for the last row
    for (int x = 0; x < width_; ++x)
    {
        cout << "+----";
    }
    cout << "+\n";
}

Cell &Maze::pick_starter_position()
{
    // randomly chooses a position
    int rng_number = getRNG();
    int width = rng_number % width_;
    int height = rng_number % height_;

    Cell &chosen = grid_[height][width];

    // setting the id and adding it to the stack
    addToStack(chosen);

    return chosen;
}

void Maze::addToStack(Cell &cell)
{
    cell.setID(nextID_++);
    cell.setVisited(true);
    list_of_cell_.push(&cell);
    idToCoordinates_[cell.getID()] = std::make_pair(cell.getX(), cell.getY());
}

void Maze::break_wall(Cell &current, Cell &next, Cell::Direction direction)
{
    current.removeWall(direction);

    switch (direction) // we must choose the opposite
    {
    case Cell::UP:
        next.removeWall(Cell::DOWN);
        break;
    case Cell::LEFT:
        next.removeWall(Cell::RIGHT);
        break;
    case Cell::DOWN:
        next.removeWall(Cell::UP);
        break;
    case Cell::RIGHT:
        next.removeWall(Cell::LEFT);
        break;
    }
}

pair<int, int>
Maze::get_neighbor_coordinate(int x, int y, Cell::Direction direction)
{
    int nx = x;
    int ny = y;
    switch (direction)
    {
    case Cell::UP:
        ny -= 1;
        break;
    case Cell::LEFT:
        nx -= 1;
        break;
    case Cell::DOWN:
        ny += 1;
        break;
    case Cell::RIGHT:
        nx += 1;
        break;
    }
    return make_pair(nx, ny);
}

void Maze::setX_Y_Neighbor(int &previous_x, int &previous_y, Cell::Direction dire, int &new_x, int &new_y)
{
    pair<int, int> new_coordinates =
        get_neighbor_coordinate(previous_x, previous_y, dire);
    new_x = new_coordinates.first;
    new_y = new_coordinates.second;
}

bool Maze::is_within_bounds(int x, int y) const
{
    return (x >= 0 && x < width_ && y >= 0 && y < height_);
}

Cell &Maze::pick_new_cell()
{
    if (list_of_cell_.empty())
    {
        throw runtime_error("Stack is empty");
    }

    Cell *previous_cell = list_of_cell_.top();
    int px = previous_cell->getX();
    int py = previous_cell->getY();

    // Try each direction in a random order
    vector<Cell::Direction> directions =
        {Cell::UP, Cell::LEFT, Cell::DOWN, Cell::RIGHT};

    shuffle(directions.begin(), directions.end(), sGenerator_);

    for (Cell::Direction direction : directions)
    {
        int nx = 0, ny = 0;
        setX_Y_Neighbor(px, py, direction, nx, ny);

        // there is a wall to break
        if (previous_cell->hasWall(direction) && is_within_bounds(nx, ny))
        {
            Cell &chosen_cell = grid_[ny][nx];
            if (!chosen_cell.isVisited())
            {
                break_wall(*previous_cell, chosen_cell, direction);
                addToStack(chosen_cell);

                return chosen_cell;
            }
        }
    }
    list_of_cell_.pop();
    return *previous_cell;
}

void Maze::generate(int h, int w)
{
    width_ = w;
    height_ = h;
    grid_ = vector<vector<Cell>>(h, vector<Cell>(w));
    nextID_ = 0;

    // Initialize the grid with coordinates
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            grid_[i][j].setCoordinates(j, i);
        }
    }

    while (!list_of_cell_.empty())
    {
        list_of_cell_.pop();
    }

    pick_starter_position();
    while (!list_of_cell_.empty())
    {
        pick_new_cell();
    }
    print();
};

int Maze::moveToNextCell(Cell &start)
{
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
            setX_Y_Neighbor(x, y, direction, nx, ny);

            Cell &neighbor = getCell(nx, ny);

            // TODO : Get the first one and not the last one ?

            // we choose the minimal distance
            if (neighbor.getWeight() < minimal_weight)
            {
                minimal_weight = neighbor.getWeight();
                chosen_cell = &neighbor;
            }
        }
    }

    if (chosen_cell == nullptr)
    {
        throw std::runtime_error("No valid moves available from the start cell.");
    }

    return chosen_cell->getID();
}

int Maze::getWidth() const { return width_; };

int Maze::getHeight() const { return height_; };

Cell &Maze::getCellFromID(int id)
{
    auto it = idToCoordinates_.find(id);
    if (it != idToCoordinates_.end())
    {
        int x = it->second.first;
        int y = it->second.second;
        return getCell(x, y);
    }
    throw std::runtime_error("Cell ID not found.");
}

void Maze::print_id_map() const
{
    std::cout << "ID to Coordinates Map:\n";
    for (const auto &entry : idToCoordinates_)
    {
        int id = entry.first;
        int x = entry.second.first;
        int y = entry.second.second;
        std::cout << "ID: " << id << " -> Coordinates: (" << x << ", " << y << ")\n";
    }
}
