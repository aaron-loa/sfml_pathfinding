#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <random>
#include <list>
#include <queue>
#include <SFML/System/Sleep.hpp>
#include "stopwatch.hpp"
#include "hNode.hpp"
#include "hGlobals.hpp"
#include "hPath.hpp"
#include "hRender.hpp"

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);

sf::Vector2i mouse_cords;

stopwatch t;
void node_config_for_maze(std::vector<std::vector<Node>> &grid)
{
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[0].size(); ++j)
        {
            grid[i][j].i = i;
            grid[i][j].j = j;
            grid[i][j].wall_neighbours.clear();
            grid[i][j].wall = true;
            grid[i][j].visited = false;
            change_color(wall_color, &grid[i][j]);
        }
    }
}
void prim(std::vector<std::vector<Node>> &grid)
{
    node_config_for_maze(grid);
    std::vector<Node *> openSet;
    int k = 0, x;
    Node *current = &grid[0][0];
    current->wall = false;
    current->visited = true;
    current->gen_neighbours_wall(grid);
    change_color(default_color, current);
    for (int i = 0; i < current->wall_neighbours.size(); ++i)
    {
        openSet.push_back(current->wall_neighbours[i]);
    }
    while (!openSet.empty())
    {
        k = 0;
        std::uniform_int_distribution<int> distribution(0, openSet.size() - 1);
        // std::cout << distribution(generator) << " " << distribution(generator) << " " << distribution(generator) << " " << distribution(generator);
        x = distribution(generator);
        current = openSet[x];
        current->gen_neighbours_wall(grid);
        for (int i = 0; i < current->wall_neighbours.size(); ++i)
        {
            if (current->wall_neighbours[i]->visited == true)
            {
                ++k;
            }
        }
        if (k == 1)
        {
            change_color(default_color, current);
            current->wall = false;
            current->visited = true;
            for (int i = 0; i < current->wall_neighbours.size(); ++i)
            {
                if (current->wall_neighbours[i]->wall == true)
                {
                    openSet.push_back(current->wall_neighbours[i]);
                }
            }
        }
        std::swap(openSet[x], openSet[openSet.size() - 1]);
        openSet.pop_back();
    }
}

void help()
{

    std::cout << "\n          H - prints this help message.\n";
    std::cout << "  Left click - changes the current cursor position to a wall.\n";
    std::cout << "Middle click - sets the starting point of the path.\n";
    std::cout << " Right click - sets the end point of the path.\n";
    std::cout << "           R - changes the current cursor position to default.\n";
    std::cout << "       Space - clears the screen, changes everything to default.\n";
    std::cout << "           C - clears the previous path.\n";
    std::cout << "           B - generates walls in random points.\n";
    std::cout << "           M - generates a maze like structure.\n";
    std::cout << "           N - changes from 4 neighbours mode to 8, and vice versa.\n\n";

    std::cout << "           D - Djikstra's algorithm.\n";
    std::cout << "           A - A*\n";
    std::cout << "           Q - BFS\n";
    std::cout << "           W - DFS\n\n";
}

void invoke(Node *s, Node *e, bool (*alg)(Node *, Node *, std::vector<std::vector<Node>> &))
{
    t.reset();
    if (alg(s, e, grid_global))
    {
        std::cout << "  found path!\n";
    }
    else
    {
        std::cout << "  no path!\n";
    }
    std::cout << "  Time elapsed: " << t.elapsed() << "\n";
}

void change_mode()
{
    if (neighbour_4)
    {
        std::cout << "\n  Changed mode to 8 neighbours.\n";
    }
    else
    {
        std::cout << "\n  Changed mode to 4 neighbours.\n";
    }
    neighbour_4 = !neighbour_4;
}
int main()
{
    std::cin.tie(0);
    std::cout.tie(0);
    help();
    rectangle.setOutlineColor(sf::Color(0, 0, 0));
    // rectangle.setOutlineThickness(1);
    rectangle.setSize(sf::Vector2f(15, 15));
    sf::Event event;
    int m = n - 1;
    Node *start = &grid_global[0][0];
    Node *end = &grid_global[n - 1][n - 1];
    // window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    // gen_bombs(grid_global);
    update_screen();
    // game loop
    while (window.isOpen())
    {
        while (window.waitEvent(event))
        {
            mouse_cords = sf::Mouse::getPosition(window);
            mouse_cords.x = (mouse_cords.x - 10) / 15;
            mouse_cords.y = (mouse_cords.y - 10) / 15;
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // change to wall
                if (mouse_cords.y >= 0 && mouse_cords.y <= n && mouse_cords.x >= 0 && mouse_cords.x <= n)

                {
                    change_color(wall_color, &grid_global[mouse_cords.y][mouse_cords.x]);
                    grid_global[mouse_cords.y][mouse_cords.x].wall = true;
                    update_screen();
                }
                // clear_prev_path(grid_global);
                // t.reset();
                // if (a_star(start, end, grid_global))
                //{
                //     std::cout << "found path!\n";
                // }
                // else
                //{
                //     std::cout << " no path!\n";
                // }
                // std::cout << "\nTime elapsed: " << t.elapsed() << "\n";
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                if (mouse_cords.y >= 0 && mouse_cords.y < n && mouse_cords.x >= 0 && mouse_cords.x < n)
                { // change to end
                    change_color(default_color, end);
                    end = &grid_global[mouse_cords.y][mouse_cords.x];
                    change_color(ending_point_color, end);
                    end->wall = false;
                    update_screen();
                }
                // t.reset();
                // if (a_star(start, end, grid_global))
                //{
                //     std::cout << "found path!\n";
                // }
                // else
                //{
                //     std::cout << "no path!\n";
                // }
                // std::cout << "\nTime elapsed: " << t.elapsed() << "\n";
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
            {
                if (mouse_cords.y >= 0 && mouse_cords.y < n && mouse_cords.x >= 0 && mouse_cords.x < n) // change to start
                {
                    change_color(default_color, start);
                    start = &grid_global[mouse_cords.y][mouse_cords.x];
                    change_color(starting_point_color, start);
                    grid_global[mouse_cords.y][mouse_cords.x].wall = false;
                    update_screen();
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                if (mouse_cords.y >= 0 && mouse_cords.y < n && mouse_cords.x >= 0 && mouse_cords.x < n)
                {
                    change_color(default_color, &grid_global[mouse_cords.y][mouse_cords.x]);
                    grid_global[mouse_cords.y][mouse_cords.x].wall = false;
                    update_screen();
                }
                // clear_prev_path(grid_global);
                // t.reset();
                // if (a_star(start, end, grid_global))
                //{
                //     std::cout << "found path!\n";
                // }
                // else
                //{
                //     std::cout << " no path!\n";
                // }
                // std::cout << "\nTime elapsed: " << t.elapsed() << "\n";
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                grid_global = std::vector<std::vector<Node>>(n, std::vector<Node>(n));
                start = &grid_global[0][0];
                end = &grid_global[n - 1][n - 1];
                std::pair<int, int> starting_point = {0, 0};
                std::pair<int, int> ending_point = {m, m};
                update_screen();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
            {
                gen_bombs(grid_global);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                std::cout << "\n  djikstra\n";
                invoke(start, end, &djikstra);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                std::cout << "\n  a*\n";
                invoke(start, end, &a_star);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                std::cout << "\n  bfs\n";
                invoke(start, end, &bfs);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                std::cout << "\n  dfs\n";
                invoke(start, end, &dfs);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            {
                for (auto i : grid_global)
                    for (auto j : i)
                        change_color(wall_color, &j);
                prim(grid_global);
                update_screen();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
            {
                clear_prev_path();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
            {
                help();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
            {
                change_mode();
                sf::sleep(sf::milliseconds(100));
            }
        }
    }
    return 0;
}
