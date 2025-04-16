#include "Cell.hpp"
#include "Maze.hpp"
#include <random>
#include <iostream>

int main()
{
    Maze a = Maze(2, 2);
    a.pick_starter_position();
    a.print();
    a.pick_new_cell();
    a.print();
}