#include "hRender.hpp"
#include <SFML/Graphics.hpp>
#include "hNode.hpp"
#include <vector>
#include "hGlobals.hpp"
void change_color(const sf::Color &color, Node *node_to_change)
{
    node_to_change->color = color;
    // update_screen();
}

void update_screen()
{
    window.clear();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            rectangle.setFillColor(grid_global[i][j].color);
            rectangle.setPosition(j * 15 + 10, i * 15 + 10);
            window.draw(rectangle);
        }
    }
    window.display();
}

void gen_bombs(std::vector<std::vector<Node>> &grid)
{
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[0].size(); ++j)
        {
            grid[i][j].gen_wall();
        }
    }
    update_screen();
}

void clear_prev_path()
{
    for (int i = 0; i < grid_global.size(); ++i)
    {
        for (int j = 0; j < grid_global[0].size(); ++j)
        {
            if (grid_global[i][j].color == path_color || grid_global[i][j].color == djikstra_visited_color || grid_global[i][j].color == visited_color ||
                grid_global[i][j].color == bfs_visited_color || grid_global[i][j].color == dfs_visited_color || grid_global[i][j].color == dfs_color)
            {
                grid_global[i][j].color = default_color;
            }
        }
    }
    update_screen();
}