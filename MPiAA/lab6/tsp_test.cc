#include "tsp.h"

#include "../catch.hpp"
#include "bnb.h"

using namespace std;

// For a circilar path get its reverse.

vector<int> reversed(const vector<int> &path) {
  if (path.empty()) {
    return vector<int>{};
  }
  vector<int> result = {path[0]};  // first item is a start vertex
  result.insert(result.end(), path.rbegin(),
                path.rend());  // add vertices in reverse order
  result.pop_back();           // remove duplicated start vertex
  return result;
}

// From two possible directions for a circlular path choose one with min second
// vertex.
vector<int> min_dir(const vector<int> &path) {
  if (path.size() <= 1) {
    return path;
  }
  const auto reversed_path = reversed(path);
  return (path[1] <= reversed_path[1] ? path : reversed_path);
}

TEST_CASE("[allPermutation] Empty graph", "[tsp]") {
  Graph g{};
  CHECK(allPermutations(g, 0) == vector<int>{});
}

TEST_CASE("[allPermutation] Single vertex", "[tsp]") {
  Graph g{};
  g.add_vertex(0);
  CHECK(allPermutations(g, 0) == vector<int>{});
}

TEST_CASE("[allPermutation] One edge", "[tsp]") {
  Graph g{{0, 1, 2.5}};
  CHECK(allPermutations(g, 0) == vector<int>{0, 1});
}

TEST_CASE("[allPermutation] Three vertices, three edges", "[tsp]") {
  Graph g{{0, 1, 2.5}, {0, 2, 0.5}, {1, 2, 1.0}};
  const auto result = allPermutations(g, 0);
  const auto expected = vector<int>{0, 1, 2};
  CHECK(min_dir(result) == expected);
}

TEST_CASE("[allPermutation] Several vertices", "[tsp]") {
  Graph g{{0, 1, 6.0}, {0, 2, 4.0}, {0, 3, 1.0},
          {1, 2, 3.5}, {1, 3, 2.0}, {2, 3, 5.0}};
  const auto result = allPermutations(g, 0);
  const auto expected = vector<int>{0, 2, 1, 3};
  CHECK(min_dir(result) == expected);
}

TEST_CASE("[allPermutation] Many vertices", "[tsp]") {
  Graph g{{0, 1, 2.0}, {0, 2, 4.0}, {0, 3, 1.0}, {0, 4, 2.5}, {1, 2, 3.6},
          {1, 3, 6.0}, {1, 4, 3.0}, {2, 3, 7.0}, {2, 4, 5.0}, {3, 4, 9.0}};
  const auto result = allPermutations(g, 0);
  const auto expected = vector<int>{0, 3, 2, 1, 4};
  CHECK(min_dir(result) == expected);
}

TEST_CASE("[allPermutation] Unreachable vertex", "[tsp]") {
  Graph g{{0, 1, 2.5}, {1, 2, 1.0}, {0, 2, 1.0}, {3, 4, 0.7}};
  CHECK(allPermutations(g, 0) == vector<int>{});
  CHECK(allPermutations(g, 3) == vector<int>{});
}

TEST_CASE("[allPermutation] No looped path", "[tsp]") {
  Graph g{{0, 1, 2.5}, {0, 2, 1.0}, {2, 3, 7.0}};
  CHECK(allPermutations(g, 0) == vector<int>{});
  CHECK(allPermutations(g, 1) == vector<int>{});
}

/*=========================================================*/
/*=========================================================*/
/*=========================================================*/
/*=========================================================*/
/*=========================================================*/
/*=========================================================*/

TEST_CASE("[BnB] Empty graph", "[tsp]") {
  Graph g{};
  CHECK(tsp_BnB(g, 0) == vector<int>{});
}

TEST_CASE("[BnB] Single vertex", "[tsp]") {
  Graph g{};
  g.add_vertex(0);
  CHECK(tsp_BnB(g, 0) == vector<int>{});
}

TEST_CASE("[BnB] One edge", "[tsp]") {
  Graph g{{0, 1, 2.5}};
  CHECK(tsp_BnB(g, 0) == vector<int>{0, 1});
}

TEST_CASE("[BnB] Three vertices, three edges", "[tsp]") {
  Graph g{{0, 1, 2.5}, {0, 2, 0.5}, {1, 2, 1.0}};
  const auto result = tsp_BnB(g, 0);
  const auto expected = vector<int>{0, 1, 2};
  CHECK(min_dir(result) == expected);
}

TEST_CASE("[BnB] Several vertices", "[tsp]") {
  Graph g{{0, 1, 6.0}, {0, 2, 4.0}, {0, 3, 1.0},
          {1, 2, 3.5}, {1, 3, 2.0}, {2, 3, 5.0}};
  const auto result = tsp_BnB(g, 0);
  const auto expected = vector<int>{0, 2, 1, 3};
  CHECK(min_dir(result) == expected);
}

TEST_CASE("[BnB] Many vertices", "[tsp]") {
  Graph g{{0, 1, 2.0}, {0, 2, 4.0}, {0, 3, 1.0}, {0, 4, 2.5}, {1, 2, 3.6},
          {1, 3, 6.0}, {1, 4, 3.0}, {2, 3, 7.0}, {2, 4, 5.0}, {3, 4, 9.0}};
  const auto result = tsp_BnB(g, 0);
  const auto expected = vector<int>{0, 3, 2, 1, 4};
  CHECK(min_dir(result) == expected);
}

TEST_CASE("[BnB] Unreachable vertex", "[tsp]") {
  Graph g{{0, 1, 2.5}, {1, 2, 1.0}, {0, 2, 1.0}, {3, 4, 0.7}};
  CHECK(tsp_BnB(g, 0) == vector<int>{});
  CHECK(tsp_BnB(g, 3) == vector<int>{});
}

TEST_CASE("[BnB] No looped path", "[tsp]") {
  Graph g{{0, 1, 2.5}, {0, 2, 1.0}, {2, 3, 7.0}};
  CHECK(tsp_BnB(g, 0) == vector<int>{});
  CHECK(tsp_BnB(g, 1) == vector<int>{});
}