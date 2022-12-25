#include "tsp.h"

#include <algorithm>
#include <iostream>

using std::vector;

auto hasPath(const Graph &g, const std::vector<int> &vertices) -> bool {
  bool res = true;
  for (int i = 1; res && i < vertices.size(); i++) {
    res = g.has_edge(vertices[i - 1], vertices[i]);
  }
  // if (res) res = g.has_edge(vertices.back(), vertices[0]);
  return res;
}

auto allPermutations(const Graph &g, int start_vertex) -> vector<int> {
  auto vertices = g.get_vertices();
  for (auto it = vertices.begin(); it < vertices.end(); ++it) {
    if (*it == start_vertex) {
      vertices.erase(it);
      break;
    }
  }
  vertices.insert(vertices.begin(), start_vertex);
  vertices.emplace_back(start_vertex);
  double minLen{std::numeric_limits<double>::max()};
  std::vector<int> path;
  do {
    if (hasPath(g, vertices)) {
      double tmp = pathLen(g, vertices);
      if (tmp < minLen) {
        minLen = tmp;
        path = vertices;
      }
    }
  } while (std::next_permutation(vertices.begin() + 1, vertices.end() - 1));

  if (!path.empty()) path.pop_back();
  return path;
}

auto Next(const Graph &graph, vector<int> &path) -> int {
  std::pair<int, double> min_edge;
  min_edge.second = std::numeric_limits<double>::max();
  min_edge.first = -1;
  const auto &edges = graph.get_adjacent_edges(path.back());

  for (auto elem : edges) {
    if (std::find(path.begin(), path.end(), elem.first) == path.end()) {
      if (elem.second < min_edge.second) min_edge = elem;
    }
  }
  return min_edge.first;
}

auto greedy(const Graph &graph, int start_vertex) -> vector<int> {
  vector<int> vertices = graph.get_vertices();

  auto edges = graph.get_adjacent_edges(start_vertex);

  if (vertices.size() == 0 || graph.has_vertex(start_vertex) == false)
    return vector<int>{};

  vector<int> path;
  vector<int> visited;

  path.reserve(vertices.size() + 1);

  path.emplace_back(start_vertex);
  while (path.size() != graph.get_vertices().size()) {
    int vertex = Next(graph, path);
    if (vertex == -1) {
      return std::vector<int>();
    }
    path.emplace_back(vertex);
  }
  if (!graph.has_edge(path[0], path.back())) {
    return std::vector<int>();
  }
  return path;
}
