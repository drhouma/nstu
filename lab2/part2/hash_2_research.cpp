#include "dictionary.h"
#include <random>
#include <vector>
#include <chrono>
#include <iostream>
#include <exception>
#include "random_string.h"


const int N = 1e+6;
const int M = 1e+5;

int main () {
    Dictionary d(HashFunc::hash2);
    std::random_device rd;
    std::default_random_engine engine{rd()};
    std::string characters =   "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::vector<string> rs(N);
    for (int i = 0; i < N; i++) {
        rs[i] = random_string(3, 20, engine, characters);
    }

    auto start = std::chrono::high_resolution_clock().now();
    for (int i = 0; i < N; i++) {
        d.set(rs[i], "1");
    }
    auto end = std::chrono::high_resolution_clock().now();
    auto time = std::chrono::duration<double>(end - start).count();
    std::cout << "вставка "<< N <<" случайных строк заняла " << time << " секунд" << std::endl;

    start = std::chrono::high_resolution_clock().now();
    for (int i = 0; i < M; i++) {
        d.get(rs[i]);
    }
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "поиск "<< M <<" M строк занял " << time << " секунд" << std::endl;
    std::cout << "всего коллизий: " << d.CountTotalPercussion() << '\n';

    
}