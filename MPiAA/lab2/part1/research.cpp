#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "count_sort.h"
#include <iostream>

const int N = 1e+4;

int main() {
    std::vector<int> rn_my(N), rn_sort(N), big_dist_my(N), big_dist_sort(N);
    std::random_device rd;
    std::default_random_engine engine{rd()};
    std::uniform_int_distribution<int> dist{-1000, 1000};
    std::uniform_int_distribution<int> big_dist{-50000000, 50000000};
    for (int i = 0; i < N; i++) {
        rn_sort[i] = rn_my[i] = dist(engine);
        big_dist_my[i] = big_dist_sort[i] = big_dist(engine);
    }

    auto start = std::chrono::high_resolution_clock().now();
    std::sort(rn_sort.begin(), rn_sort.end());
    auto end = std::chrono::high_resolution_clock().now();
    auto time = std::chrono::duration<double>(end - start).count();
    std::cout << "std::sort отработал на "<< N <<" случайных числах за " << time << " секунд" << std::endl;

    start = std::chrono::high_resolution_clock().now();
    count_sort(rn_my, -1000, 1001);
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "count_sort отработал на "<< N <<" случайных числах за " << time << " секунд" << std::endl;


    start = std::chrono::high_resolution_clock().now();
    std::sort(big_dist_sort.begin(), big_dist_sort.end());
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "std::sort отработал на "<< N <<" случайных числах в большом диапазоне за " << time << " секунд" << std::endl;

    start = std::chrono::high_resolution_clock().now();
    count_sort(big_dist_my, -50000000, 50000001);
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "count_sort отработал на "<< N <<" случайных числах в большом диапазоне за " << time << " секунд" << std::endl;
}