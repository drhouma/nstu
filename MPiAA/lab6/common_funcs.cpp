#include "common_funcs.h"
using std::vector;

auto pathLen(const Graph &g, vector<int> &vec) -> double {
  double res{0};
  if (vec.size() == 0) return 10000000;

  for (int i = 1; i < vec.size(); i++) {
    res += g.edge_weight(vec[i - 1], vec[i]);
  }
  return res;
}

auto minPath(const Graph &g, vector<int> &vec1, vector<int> &vec2)
    -> vector<int> {
  if (pathLen(g, vec1) < pathLen(g, vec2)) return vec1;
  return vec2;
}