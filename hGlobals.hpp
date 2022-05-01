#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "hNode.hpp"

extern const int n;
extern bool neighbour_4;
extern std::vector<std::vector<Node>> grid_global;
extern sf::RectangleShape rectangle;
extern sf::RenderWindow window;
extern const sf::Color default_color;
extern const sf::Color path_color;
extern const sf::Color starting_point_color;
extern const sf::Color wall_color;
extern const sf::Color ending_point_color;
extern const sf::Color visited_color;
extern const sf::Color djikstra_visited_color;
extern const sf::Color bfs_visited_color;
extern const sf::Color dfs_visited_color;
extern const sf::Color dfs_color;

// global const valuessf::Color default_color = sf::Color::White;