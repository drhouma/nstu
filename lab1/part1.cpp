#include <chrono>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>

const int N = 10e+5;

using std::list;
using std::set;
using std::vector;

int main() {
  vector<int> vector;
  list<int> list;
  set<int> set;

  auto start = std::chrono::high_resolution_clock().now();
  for (int i = 0; i < N; i++) {
    vector.push_back(i);
  }
  auto end = std::chrono::high_resolution_clock().now();

  auto time = std::chrono::duration<double>(end - start).count();
  vector.clear();
  std::cout << "вставка " << N
            << " элементов в vector<int> методом push_back заняла :" << time
            << " секунд" << std::endl;

  start = std::chrono::high_resolution_clock().now();
  for (int i = 0; i < N; i++) {
    vector.insert(vector.begin(), i);
  }
  end = std::chrono::high_resolution_clock().now();

  time = std::chrono::duration<double>(end - start).count();
  vector.clear();
  std::cout << "вставка " << N
            << " элементов в vector<int> методом insert заняла :" << time
            << " секунд" << std::endl
            << std::endl;

  start = std::chrono::high_resolution_clock().now();
  for (int i = 0; i < N; i++) {
    list.push_back(i);
  }
  end = std::chrono::high_resolution_clock().now();

  time = std::chrono::duration<double>(end - start).count();
  list.clear();
  std::cout << "вставка " << N
            << " элементов в list<int> методом push_back заняла :" << time
            << " секунд" << std::endl;

  start = std::chrono::high_resolution_clock().now();
  for (int i = 0; i < N; i++) {
    list.insert(list.begin(), i);
  }
  end = std::chrono::high_resolution_clock().now();

  time = std::chrono::duration<double>(end - start).count();
  list.clear();
  std::cout << "вставка " << N
            << " элементов в list<int> методом insert заняла :" << time
            << " секунд" << std::endl
            << std::endl;

  start = std::chrono::high_resolution_clock().now();
  for (int i = 0; i < N; i++) {
    set.emplace();
  }
  end = std::chrono::high_resolution_clock().now();

  time = std::chrono::duration<double>(end - start).count();
  set.clear();
  std::cout << "вставка " << N << " элементов в set<int, int> заняла :" << time
            << " секунд" << std::endl;
}