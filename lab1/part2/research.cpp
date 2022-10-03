#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
#include "algorithms.h"
const int N = 5e+4;

int main () {
    std::vector<int> rn(N), identical_numbers(N), no_duplicate_numbers(N);
    std::random_device rd;
    std::default_random_engine engine{rd()};
    std::uniform_int_distribution<int> dist{0, N};
    for (int i = 0; i < N; i++) {
        rn[i] = dist(engine);
        identical_numbers[i] = 1;
        no_duplicate_numbers[i] = i;
    }

    auto start = std::chrono::high_resolution_clock().now();
    has_duplicates(rn);
    auto end = std::chrono::high_resolution_clock().now();
    auto time = std::chrono::duration<double>(end - start).count();
    std::cout << "has_duplicates на массиве "<< N <<" случайных чисел работал " << time << " секунд" << std::endl;

    start = std::chrono::high_resolution_clock().now();
    has_duplicates_naive(rn);
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "has_duplicates_naive на массиве "<< N <<" случайных чисел работал " << time << " секунд" << std::endl;

    start = std::chrono::high_resolution_clock().now();
    get_duplicates(rn);
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "get_duplicates на массиве "<< N <<" случайных чисел работал " << time << " секунд" << std::endl;

    start = std::chrono::high_resolution_clock().now();
    get_duplicates_naive(rn);
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "get_duplicates_naive на массиве "<< N <<" случайных чисел работал " << time << " секунд" << std::endl;
    std::cout << '\n';



    start = std::chrono::high_resolution_clock().now();
    has_duplicates(identical_numbers);
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "has_duplicates на массиве "<< N <<" одинаковых чисел работал " << time << " секунд" << std::endl;

    start = std::chrono::high_resolution_clock().now();
    has_duplicates_naive(identical_numbers);
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "has_duplicates_naive на массиве "<< N <<" одинаковых чисел работал " << time << " секунд" << std::endl;

    start = std::chrono::high_resolution_clock().now();
    get_duplicates(identical_numbers);
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "get_duplicates на массиве "<< N <<" одинаковых чисел работал " << time << " секунд" << std::endl;

    start = std::chrono::high_resolution_clock().now();
    get_duplicates_naive(identical_numbers);
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "get_duplicates_naive на массиве "<< N <<" одинаковых чисел работал " << time << " секунд" << std::endl;
    std::cout << '\n';





    start = std::chrono::high_resolution_clock().now();
    has_duplicates(identical_numbers);
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "has_duplicates на массиве "<< N <<" не повторяющихся чисел работал " << time << " секунд" << std::endl;

    start = std::chrono::high_resolution_clock().now();
    has_duplicates_naive(identical_numbers);
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "has_duplicates_naive на массиве "<< N <<" не повторяющихся чисел работал " << time << " секунд" << std::endl;

    start = std::chrono::high_resolution_clock().now();
    get_duplicates(identical_numbers);
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "get_duplicates на массиве "<< N <<" не повторяющихся чисел работал " << time << " секунд" << std::endl;

    start = std::chrono::high_resolution_clock().now();
    get_duplicates_naive(identical_numbers);
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "get_duplicates_naive на массиве "<< N <<" не повторяющихся чисел работал " << time << " секунд" << std::endl;
}
