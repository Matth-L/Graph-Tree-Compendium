#include "Maze.hpp"
#include <iostream>
#include <algorithm>

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
            cout << (walls[Cell::UP] ? "+--" : "+  ");
        }
        // EOL top walls
        cout << "+\n";

        // the left wall and cell itself
        for (int x = 0; x < width_; ++x)
        {
            const Cell &cell = grid_[y][x];
            const array<bool, 4> &walls = cell.getWalls();
            cout << (walls[Cell::LEFT] ? "| " : "  ") << cell.getID();
        }
        // EOL left walls and cells
        cout << "|\n";
    }

    // bottom wall for the last row
    for (int x = 0; x < width_; ++x)
    {
        cout << "+--";
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
    addToStack(chosen, 0);

    return chosen;
}

void Maze::addToStack(Cell &cell, int previous_id)
{
    cell.setID(previous_id + 1);
    cell.setVisited(true);
    list_of_cell_.push(&cell);
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

pair<int, int> Maze::get_neighbor_coordinate(int x, int y, Cell::Direction direction)
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
    vector<Cell::Direction> directions = {Cell::UP, Cell::LEFT, Cell::DOWN, Cell::RIGHT};
    shuffle(directions.begin(), directions.end(), sGenerator_);

    for (Cell::Direction direction : directions)
    {
        pair<int, int> new_coordinates =
            get_neighbor_coordinate(px, py, direction);
        int nx = new_coordinates.first;
        int ny = new_coordinates.second;

        // there is a wall to break
        if (previous_cell->hasWall(direction) && is_within_bounds(nx, ny))
        {
            Cell &chosen_cell = grid_[ny][nx];
            if (!chosen_cell.isVisited())
            {
                break_wall(*previous_cell, chosen_cell, direction);
                addToStack(chosen_cell, previous_cell->getID());

                cout << "direction " << direction << endl;
                cout << "prev " << previous_cell->numberOfWall() << endl;
                cout << "next " << chosen_cell.numberOfWall() << endl;

                return chosen_cell;
            }
        }
    }
}
