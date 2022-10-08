#ifndef NSTU_LAB1_ALGORITHMS
#define NSTU_LAB1_ALGORITHMS
#include <vector>

// хз почему я не сделал константные ссылки
auto has_duplicates(std::vector<int> array)       -> bool;
auto has_duplicates_naive(std::vector<int> array) -> bool;

auto get_duplicates(std::vector<int> array)       -> std::vector<int>;
auto get_duplicates_naive(std::vector<int> array) -> std::vector<int>;
#endif