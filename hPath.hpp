#pragma once
#include "hNode.hpp"
#include <set>
#include <vector>
#include "hGlobals.hpp"
#include <iostream>

struct Compare_for_a_star
{
    bool operator()(const Node *rhs, const Node *lhs);
};

struct Compare_for_djikstra
{
    bool operator()(const Node *rhs, const Node *lhs);
};

bool djikstra(Node *start, Node *end, std::vector<std::vector<Node>> &grid);

bool a_star(Node *start, Node *end, std::vector<std::vector<Node>> &grid);

bool bfs(Node *start, Node *end, std::vector<std::vector<Node>> &grid);

bool dfs(Node *start, Node *end, std::vector<std::vector<Node>> &grid);