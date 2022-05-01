#include "hGlobals.hpp"
#include <SFML/Graphics.hpp>
#include "hNode.hpp"

const int n = 50;
bool neighbour_4 = true;
std::vector<std::vector<Node>> grid_global(n, std::vector<Node>(n));
sf::RectangleShape rectangle;
sf::RenderWindow window(sf::VideoMode(770, 770), "Pathfinding", sf::Style::Close);
const sf::Color default_color = sf::Color::White;
const sf::Color path_color = sf::Color::Blue;
const sf::Color starting_point_color = sf::Color::Green;
const sf::Color wall_color = sf::Color::Black;
const sf::Color ending_point_color = sf::Color::Red;
const sf::Color visited_color = sf::Color::Magenta;
const sf::Color djikstra_visited_color = sf::Color::Yellow;
const sf::Color bfs_visited_color(255, 0, 0);
const sf::Color dfs_visited_color(234, 182, 118);
const sf::Color dfs_color(226, 135, 67);