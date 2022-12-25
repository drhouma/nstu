#ifndef COMMON_FUNCS_H
#define COMMON_FUNCS_H
#include <vector>

#include "graph.h"

auto pathLen(const Graph &g, std::vector<int> &vec) -> double;
auto minPath(const Graph &g, std::vector<int> &vec1, std::vector<int> &vec2)
    -> std::vector<int>;
#endif