#ifndef NSTU_BNB_H
#define NSTU_BNB_H
#include <algorithm>
#include <vector>

#include "common_funcs.h"
#include "graph.h"
auto tsp_BnB(const Graph &graph, int start_vertex) -> std::vector<int>;
auto BnB(const Graph &graph, std::vector<int> visited,
         std::vector<int> bestPath) -> std::vector<int>;
#endif