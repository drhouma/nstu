#include "bnb.h"

#include <iostream>
using std::vector;

auto tsp_BnB(const Graph& graph, int start_vertex) -> vector<int> {
  vector<int> vertices = graph.get_vertices();

  auto edges = graph.get_adjacent_edges(start_vertex);

  if (vertices.size() == 0 || graph.has_vertex(start_vertex) == false)
    return vector<int>{};

  vector<int> bestPath;
  vector<int> visited;

  //   visited.reserve(vertices.size() + 1);
  visited.emplace_back(start_vertex);
  auto res = BnB(graph, visited, bestPath);
  if (res.size() != 0) res.pop_back();
  return res;
}

auto edgeInPath(const Graph& g, int first, int second, const vector<int>& path)
    -> bool {
  for (int i = 1; i < path.size(); i++) {
    if (path[i - 1] == first && path[i] == second) return true;
  }
  return false;
}

auto lowerBound(const Graph& g, vector<int>& path) -> double {
  const auto& vertices = g.get_vertices();
  double sum{0};
  if (path.size() == 0) return std::numeric_limits<int>::max();
  std::vector<double> m_edges;
  std::vector<double> m_edges_in_path;
  double min_weight;
  int min_edge;

  for (auto vertex : vertices) {
    const auto& edges = g.get_adjacent_edges(vertex);
    for (auto edge : edges) {
      if (edgeInPath(g, vertex, edge.first, path)) {
        m_edges_in_path.emplace_back(edge.second);
      } else {
        m_edges.emplace_back(edge.second);
      }
    }
    for (int j = 0; j < 2 && j < m_edges_in_path.size(); j++) {
      min_weight = std::numeric_limits<double>::max();
      min_edge = 0;
      for (int i = 0; i < m_edges_in_path.size(); i++) {
        if (m_edges_in_path[i] < min_weight) {
          min_edge = i;
          min_weight = m_edges_in_path[i];
        }
      }
      m_edges_in_path[min_edge] = std::numeric_limits<double>::max();
      sum += min_weight;
    }
    if (m_edges_in_path.size() < 2) {
      for (int j = m_edges_in_path.size(); j < 2; j++) {
        min_weight = std::numeric_limits<double>::max();
        min_edge = 0;
        for (int i = 0; i < m_edges.size(); i++) {
          if (m_edges[i] < min_weight) {
            min_edge = i;
            min_weight = m_edges[i];
          }
        }
        m_edges[min_edge] = std::numeric_limits<double>::max();
        sum += min_weight;
      }
    }
    m_edges_in_path.clear();
    m_edges.clear();
  }
  return sum / 2;
}

auto BnB(const Graph& graph, vector<int> visited, vector<int> bestPath)
    -> vector<int> {
  if (visited.size() == graph.get_vertices().size()) {
    if (!graph.has_edge(visited.back(), visited[0])) return bestPath;
    visited.emplace_back(visited[0]);
    return minPath(graph, bestPath, visited);
  }
  auto edges = graph.get_adjacent_edges(visited.back());
  for (auto elem : edges) {
    if (std::find(visited.begin(), visited.end(), elem.first) ==
        visited.end()) {
      visited.push_back(elem.first);
      if (lowerBound(graph, visited) < pathLen(graph, bestPath)) {
        auto path = BnB(graph, visited, bestPath);

        bestPath = minPath(graph, path, bestPath);
      }
      visited.pop_back();
    }
  }
  return bestPath;
}