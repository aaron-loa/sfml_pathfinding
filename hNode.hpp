#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
struct Node
{
    int i;
    int j;
    int g = INT32_MAX;
    double h = INT32_MAX;
    double f = INT32_MAX;
    sf::Color color = sf::Color::White;
    std::pair<int, int> came_from{-2, -2};
    bool wall = false;
    std::vector<Node *> neighbours;
    std::vector<Node *> wall_neighbours;
    bool visited = false;
    void gen_neighbours_wall(std::vector<std::vector<Node>> &grid);

    void gen_neighbours_8(std::vector<std::vector<Node>> &grid);

    void gen_neighbours_4(std::vector<std::vector<Node>> &grid);

    void get_h(Node *end);

    void gen_wall();

    bool operator<(const Node *x) const;
};