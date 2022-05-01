#include "hNode.hpp"
#include "hPath.hpp"
#include <set>
#include <stack>
#include <vector>
#include "hGlobals.hpp"
#include <iostream>
#include <queue>
#include "hRender.hpp"
bool Compare_for_a_star::operator()(const Node *rhs, const Node *lhs)
{
    return rhs->f <= lhs->f;
}

bool Compare_for_djikstra::operator()(const Node *rhs, const Node *lhs)
{
    return rhs->g <= lhs->g;
}

void node_config(std::vector<std::vector<Node>> &grid)
{
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[0].size(); ++j)
        {
            grid[i][j].i = i;
            grid[i][j].j = j;
            grid[i][j].came_from = {-2, -2};
            grid[i][j].g = INT32_MAX;
            grid[i][j].f = INT32_MAX;
            grid[i][j].h = INT32_MAX;
            grid[i][j].neighbours.clear();
        }
    }
    if (neighbour_4)
    {
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[0].size(); ++j)
            {

                grid[i][j].gen_neighbours_4(grid);
            }
        }
    }
    else
    {
        for (int i = 0; i < grid.size(); ++i)
        {
            for (int j = 0; j < grid[0].size(); ++j)
            {

                grid[i][j].gen_neighbours_8(grid);
            }
        }
    }
}
void construct_path(Node *current_node, std::vector<std::vector<Node>> &grid)
{
    int next_i = current_node->came_from.first;
    int i;
    int next_j = current_node->came_from.second;
    int j;
    int counter = 0;
    while (grid[next_i][next_j].came_from.first != -1)
    {
        // change_color(path_color, &grid[next_i][next_j]);
        // update_screen();
        grid[next_i][next_j].color = path_color;
        i = grid[next_i][next_j].came_from.first;
        j = grid[next_i][next_j].came_from.second;
        next_i = i;
        next_j = j;
        ++counter;
    }
    std::cout << "  Distance: " << counter << std::endl;
    update_screen();
}
bool djikstra(Node *start, Node *end, std::vector<std::vector<Node>> &grid)
{
    node_config(grid_global);
    Node *current;
    int tmp_g;
    std::set<Node *, Compare_for_djikstra> openSet;
    start->g = 0;
    openSet.insert(start);
    while (!openSet.empty())
    {
        current = *openSet.begin();
        if (current->i == end->i && current->j == end->j)
        {
            start->came_from = {-1, -1};
            construct_path(end, grid);
            return true;
        }
        openSet.erase(openSet.begin());
        tmp_g = current->g + 1;

        for (int i = 0; i < current->neighbours.size(); ++i)
        {
            change_color(djikstra_visited_color, current->neighbours[i]);
            if (tmp_g < current->neighbours[i]->g)
            {
                current->neighbours[i]->g = tmp_g;
                current->neighbours[i]->came_from = {current->i, current->j};
                openSet.insert(current->neighbours[i]);
            }
        }
        update_screen();
    }
    return false;
}

bool a_star(Node *start, Node *end, std::vector<std::vector<Node>> &grid)
{
    node_config(grid_global);
    int tmp_g = INT32_MAX;
    Node *current;
    std::set<Node *, Compare_for_a_star> openSet;
    start->g = 0;
    start->get_h(end);
    start->came_from = {-1, -1};
    openSet.insert(start);
    while (!openSet.empty())
    {
        current = *openSet.begin();
        if (current->i == end->i && current->j == end->j)
        {
            construct_path(current, grid);
            return true;
        }
        tmp_g = current->g + 1;
        openSet.erase(openSet.begin());
        for (int i = 0; i < current->neighbours.size(); ++i)
        {
            // change_color(to_visit_color, current->neighbours[i]);
            // update_screen();
            if (tmp_g < current->neighbours[i]->g)
            {
                change_color(visited_color, current->neighbours[i]);

                current->neighbours[i]->came_from = {current->i, current->j};
                current->neighbours[i]->g = tmp_g;
                current->neighbours[i]->get_h(end);
                openSet.insert(current->neighbours[i]);
            }
        }
        update_screen();
    }
    return false;
}

bool bfs(Node *start, Node *end, std::vector<std::vector<Node>> &grid)
{
    node_config(grid_global);
    std::queue<Node *> openSet;
    start->came_from = {-1, -1};
    openSet.push(start);
    Node *current;
    while (!openSet.empty())
    {
        current = openSet.front();
        openSet.pop();
        if (current->i == end->i && current->j == end->j)
        {
            construct_path(current, grid);
            return true;
        }
        for (int i = 0; i < current->neighbours.size(); ++i)
        {
            if (current->neighbours[i]->came_from.first == -2)
            {
                change_color(bfs_visited_color, current->neighbours[i]);
                current->neighbours[i]->came_from = {current->i, current->j};
                openSet.push(current->neighbours[i]);
            }
        }
        update_screen();
    }
    return false;
}

bool dfs(Node *start, Node *end, std::vector<std::vector<Node>> &grid)
{
    node_config(grid_global);
    std::stack<Node *> openSet;
    start->came_from = {-1, -1};
    openSet.push(start);
    Node *current;
    while (!openSet.empty())
    {
        current = openSet.top();
        change_color(dfs_color, current);
        openSet.pop();
        if (current->i == end->i && current->j == end->j)
        {
            construct_path(current, grid);
            return true;
        }
        for (int i = 0; i < current->neighbours.size(); ++i)
        {
            if (current->neighbours[i]->came_from.first == -2)
            {
                change_color(dfs_visited_color, current->neighbours[i]);
                current->neighbours[i]->came_from = {current->i, current->j};
                openSet.push(current->neighbours[i]);
            }
        }
        update_screen();
    }
    return false;
}