#include <algorithm>
#include <chrono>
#include <iostream>
#include <list>
#include <random>
#include <set>
#include <string>
#include <vector>

const int N = 1e+6;
const int M = 1e+4;

using std::list;
using std::set;
using std::vector;

int main() {
  int rn[N], rn2[M];
  std::random_device rd;
  std::default_random_engine engine{rd()};
  std::uniform_int_distribution<int> dist{0, 50000};
  for (int i = 0, *ptr = rn; i < N; i++, ptr++) {
    *ptr = dist(engine);
  }
  for (int i = 0, *ptr = rn2; i < M; i++, ptr++) {
    *ptr = dist(engine);
  }

  vector<int> vector;
  list<int> list;
  set<int> set;

  auto start = std::chrono::high_resolution_clock().now();
  for (int i = 0, *ptr = rn; i < N; i++, ptr++) {
    vector.push_back(*ptr);
  }
  auto end = std::chrono::high_resolution_clock().now();

  auto time = std::chrono::duration<double>(end - start).count();
  vector.clear();
  std::cout << "вставка " << N
            << " элементов в vector<int> методом push_back заняла :" << time
            << " секунд" << std::endl;

  start = std::chrono::high_resolution_clock().now();
  for (int i = 0, *ptr = rn; i < N; i++, ptr++) {
    vector.insert(vector.begin(), *ptr);
  }
  end = std::chrono::high_resolution_clock().now();

  time = std::chrono::duration<double>(end - start).count();
  
  std::cout << "вставка " << N
            << " элементов в vector<int> методом insert заняла :" << time
            << " секунд" << std::endl
            << std::endl;

  start = std::chrono::high_resolution_clock().now();
  for (int i = 0, *ptr = rn; i < N; i++, ptr++) {
    list.push_back(*ptr);
  }
  end = std::chrono::high_resolution_clock().now();

  time = std::chrono::duration<double>(end - start).count();
  list.clear();
  std::cout << "вставка " << N
            << " элементов в list<int> методом push_back заняла :" << time
            << " секунд" << std::endl;

  start = std::chrono::high_resolution_clock().now();
  for (int i = 0, *ptr = rn; i < N; i++, ptr++) {
    list.insert(list.begin(), *ptr);
  }
  end = std::chrono::high_resolution_clock().now();

  time = std::chrono::duration<double>(end - start).count();
  
  std::cout << "вставка " << N
            << " элементов в list<int> методом insert заняла :" << time
            << " секунд" << std::endl
            << std::endl;

  start = std::chrono::high_resolution_clock().now();
  for (int i = 0, *ptr = rn; i < N; i++, ptr++) {
    set.insert(*ptr);
  }
  end = std::chrono::high_resolution_clock().now();

  time = std::chrono::duration<double>(end - start).count();

  std::cout << "вставка " << N << " элементов в set<int, int> заняла :" << time
            << " секунд" << std::endl;

  start = std::chrono::high_resolution_clock().now();
  for (int i = 0, *ptr = rn2; i < M; i++, ptr++) {
    std::find(list.begin(), list.end(), *ptr);
    std::find(list.begin(), list.end(), *ptr);
  }
  end = std::chrono::high_resolution_clock().now();

  time = std::chrono::duration<double>(end - start).count();

  std::cout << "поиск " << M << " элементов в list<int> занял :" << time
            << " секунд" << std::endl;

  start = std::chrono::high_resolution_clock().now();
  for (int i = 0, *ptr = rn2; i < M; i++, ptr++) {
    std::find(vector.begin(), vector.end(), *ptr);
    std::find(vector.begin(), vector.end(), *ptr);
  }
  end = std::chrono::high_resolution_clock().now();

  time = std::chrono::duration<double>(end - start).count();

  std::cout << "поиск " << M << " элементов в vector<int> занял :" << time
            << " секунд" << std::endl;

  start = std::chrono::high_resolution_clock().now();
  for (int i = 0, *ptr = rn2; i < M; i++, ptr++) {
    std::find(set.begin(), set.end(), *ptr);
    std::find(set.begin(), set.end(), *ptr);
  }
  end = std::chrono::high_resolution_clock().now();

  time = std::chrono::duration<double>(end - start).count();

  std::cout << "поиск " << M << " элементов в set<int> занял :" << time
            << " секунд" << std::endl;
}