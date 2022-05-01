#include "hNode.hpp"
#include "hGlobals.hpp"
#include <SFML/Graphics.hpp>

#define chebyshev -1
#define octile 1.41421356237 - 2

void Node::gen_neighbours_wall(std::vector<std::vector<Node>> &grid)
{
    wall_neighbours.reserve(4);
    int rows = grid.size();
    int col = grid[0].size();
    // hor,vertical neighbours
    if (i + 1 < rows)
        wall_neighbours.push_back(&grid[i + 1][j]);
    if (j + 1 < col)
        wall_neighbours.push_back(&grid[i][j + 1]);
    if (i > 0)
        wall_neighbours.push_back(&grid[i - 1][j]);
    if (j > 0)
        wall_neighbours.push_back(&grid[i][j - 1]);
    wall_neighbours.shrink_to_fit();
}

void Node::gen_neighbours_8(std::vector<std::vector<Node>> &grid)
{
    neighbours.reserve(8);
    int rows = grid.size();
    int col = grid[0].size();
    // diagonal neighbours
    if (i + 1 < rows && j + 1 < col && grid[i + 1][j + 1].wall == false)
        neighbours.push_back(&grid[i + 1][j + 1]);
    if (i + 1 < rows && j > 0 && grid[i + 1][j - 1].wall == false)
        neighbours.push_back(&grid[i + 1][j - 1]);
    if (i > 0 && j + 1 < col && grid[i - 1][j + 1].wall == false)
        neighbours.push_back(&grid[i - 1][j + 1]);
    if (j > 0 && i > 0 && grid[i - 1][j - 1].wall == false)
        neighbours.push_back(&grid[i - 1][j - 1]);
    // hor,vertical neighbours
    if (i + 1 < rows && grid[i + 1][j].wall == false)
        neighbours.push_back(&grid[i + 1][j]);
    if (j + 1 < col && grid[i][j + 1].wall == false)
        neighbours.push_back(&grid[i][j + 1]);
    if (i > 0 && grid[i - 1][j].wall == false)
        neighbours.push_back(&grid[i - 1][j]);
    if (j > 0 && grid[i][j - 1].wall == false)
        neighbours.push_back(&grid[i][j - 1]);

    neighbours.shrink_to_fit();
}

void Node::gen_neighbours_4(std::vector<std::vector<Node>> &grid)
{
    neighbours.reserve(4);
    int rows = grid.size();
    int col = grid[0].size();
    // diagonal neighbours
    //  hor,vertical neighbours
    if (i + 1 < rows && grid[i + 1][j].wall == false)
        neighbours.push_back(&grid[i + 1][j]);
    if (j + 1 < col && grid[i][j + 1].wall == false)
        neighbours.push_back(&grid[i][j + 1]);
    if (i > 0 && grid[i - 1][j].wall == false)
        neighbours.push_back(&grid[i - 1][j]);
    if (j > 0 && grid[i][j - 1].wall == false)
        neighbours.push_back(&grid[i][j - 1]);
    neighbours.shrink_to_fit();
}

void Node::get_h(Node *end)
{
    double di = std::abs(end->i - i);
    double dj = std::abs(end->j - j);
    // djikstra
    // h = 0;
    // manhattan heuristic
    if (neighbour_4)
        h = di + dj;
    else
        h = (di + dj) + (octile)*std::min(di, dj);

    // h = (std::pow(di, 2) + std::pow(dj, 2));
    //  from https://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html
    // h = (di + dj) + (chebyshev)*std::min(di, dj);
    f = h + g;
}

void Node::gen_wall()
{
    if (rand() % 30 == 0)
    {
        wall = true;
        color = wall_color;
    }
}

bool Node::operator<(const Node *x) const
{
    return x->g > g;
}