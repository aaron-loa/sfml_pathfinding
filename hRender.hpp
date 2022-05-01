#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "hNode.hpp"

void change_color(const sf::Color &color, Node *node_to_change);

void update_screen();

void gen_bombs(std::vector<std::vector<Node>> &grid);

void clear_prev_path();