#include <vector>

#include "common_funcs.h"
#include "graph.h"

/// Solve Travelling Salesman Problem (TSP) for the graph:
/// Find the shortest (with a minimal total weight) tour and return it as an
/// array of vertices.
std::vector<int> greedy(const Graph &graph, int start_vertex);

auto allPermutations(const Graph &g, int start_verticle) -> std::vector<int>;