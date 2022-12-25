#include <chrono>
#include <iostream>
#include <random>

#include "bnb.h"
#include "tsp.h"
using namespace std;

// graph's vertices range = [0, vertices - 1]
auto CreateGraph(int vertices) -> Graph {
  Graph g;
  for (int i = 0; i < vertices; i++) {
    g.add_vertex(i);
  }
  std::random_device rd;
  std::default_random_engine engine{rd()};
  // dist = (1 : 20]
  std::uniform_real_distribution<double> dist(1, 20);
  for (int i = 0; i < vertices - 1; i++) {
    for (int j = i + 1; j < vertices; j++) {
      g.add_edge(i, j, dist(engine));
    }
  }
  return g;
}

int main() {
  Graph small_1{CreateGraph(4)}, small_2{CreateGraph(4)},
      small_3{CreateGraph(4)};
  Graph middle_1{CreateGraph(7)}, middle_2{CreateGraph(7)},
      middle_3{CreateGraph(7)};
  Graph large_1{CreateGraph(10)}, large_2{CreateGraph(10)},
      large_3{CreateGraph(10)};
  std::vector<int> res;

  cout << "\n**** SMALL_1 GRAPH ****\n";

  auto t1 = chrono::high_resolution_clock::now();
  res = allPermutations(small_1, 0);
  res.emplace_back(0);
  auto t2 = chrono::high_resolution_clock::now();
  auto seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- permutations -------";
  cout << "\nPath len is: " << pathLen(small_1, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = greedy(small_1, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- greedy -------";
  cout << "\nPath len is: " << pathLen(small_1, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = tsp_BnB(small_1, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- bnb -------";
  cout << "\nPath len is: " << pathLen(small_1, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  std::cout << "\n\n\n\n";
  t1 = chrono::high_resolution_clock::now();
  res = allPermutations(small_1, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- permutations -------";
  cout << "\nPath len is: " << pathLen(small_2, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = greedy(small_2, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- greedy -------";
  cout << "\nPath len is: " << pathLen(small_2, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = tsp_BnB(small_2, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- bnb -------";
  cout << "\nPath len is: " << pathLen(small_2, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  std::cout << "\n\n\n\n";
  t1 = chrono::high_resolution_clock::now();
  res = allPermutations(small_1, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- permutations -------";
  cout << "\nPath len is: " << pathLen(small_3, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = greedy(small_3, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- greedy -------";
  cout << "\nPath len is: " << pathLen(small_3, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = tsp_BnB(small_3, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- bnb -------";
  cout << "\nPath len is: " << pathLen(small_3, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  /*******************************************************************/

  cout << "\n**** MIDDLE_1 GRAPH ****\n";
  t1 = chrono::high_resolution_clock::now();
  res = allPermutations(middle_1, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- permutations -------";
  cout << "\nPath len is: " << pathLen(middle_1, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = greedy(middle_1, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- greedy -------";
  cout << "\nPath len is: " << pathLen(middle_1, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = tsp_BnB(middle_1, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- bnb -------";
  cout << "\nPath len is: " << pathLen(middle_1, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  std::cout << "\n\n\n\n\n";

  t1 = chrono::high_resolution_clock::now();
  res = allPermutations(middle_2, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- permutations -------";
  cout << "\nPath len is: " << pathLen(middle_2, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = greedy(middle_2, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- greedy -------";
  cout << "\nPath len is: " << pathLen(middle_2, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = tsp_BnB(middle_2, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- bnb -------";
  cout << "\nPath len is: " << pathLen(middle_2, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = allPermutations(middle_3, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();
  std::cout << "\n\n\n\n\n";

  cout << "\n------- permutations -------";
  cout << "\nPath len is: " << pathLen(middle_3, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = greedy(middle_3, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- greedy -------";
  cout << "\nPath len is: " << pathLen(middle_3, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = tsp_BnB(middle_3, 0);
  res.emplace_back(0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- bnb -------";
  cout << "\nPath len is: " << pathLen(middle_3, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  /*******************************************************************/

  cout << "\n**** LARGE_1 GRAPH ****\n";

  t1 = chrono::high_resolution_clock::now();
  res = allPermutations(large_1, 0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- permutations -------";
  cout << "\nPath len is: " << pathLen(large_1, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = greedy(large_1, 0);

  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- greedy -------";
  cout << "\nPath len is: " << pathLen(large_1, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = tsp_BnB(large_1, 0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- bnb -------";
  cout << "\nPath len is: " << pathLen(large_1, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = allPermutations(large_2, 0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();
  std::cout << "\n\n\n\n\n";

  cout << "\n------- permutations -------";
  cout << "\nPath len is: " << pathLen(large_2, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = greedy(large_2, 0);

  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- greedy -------";
  cout << "\nPath len is: " << pathLen(large_2, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = tsp_BnB(large_2, 0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- bnb -------";
  cout << "\nPath len is: " << pathLen(large_2, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  std::cout << "\n\n\n\n\n";

  t1 = chrono::high_resolution_clock::now();
  res = allPermutations(large_3, 0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- permutations -------";
  cout << "\nPath len is: " << pathLen(large_3, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = greedy(large_3, 0);

  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- greedy -------";
  cout << "\nPath len is: " << pathLen(large_3, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  t1 = chrono::high_resolution_clock::now();
  res = tsp_BnB(large_3, 0);
  t2 = chrono::high_resolution_clock::now();
  seconds = std::chrono::duration<double>(t2 - t1).count();

  cout << "\n------- bnb -------";
  cout << "\nPath len is: " << pathLen(large_3, res) << '\n';
  cout << "Время поиска составило " << seconds << " секунд\n";

  return 0;
}