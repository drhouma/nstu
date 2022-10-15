#include <random>
#include <vector>
#include <chrono>
#include <iostream>
#include <exception>
#include "random_string.h"
#include <map>
#include "M_N.h"

int main () {
    std::map<std::string, std::string> map;

    std::random_device rd;
    std::default_random_engine engine{rd()};
    std::string characters =   "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::vector<std::string> rs(N);
    for (int i = 0; i < N; i++) {
        rs[i] = random_string(3, 20, engine, characters);
    }



    auto start = std::chrono::high_resolution_clock().now();
    for (int i = 0; i < N; i++) {
        map.insert(make_pair(rs[i], "1"));
    }
    auto end = std::chrono::high_resolution_clock().now();
    auto time = std::chrono::duration<double>(end - start).count();
    std::cout << "вставка "<< N <<" случайных строк в std::map заняла " << time << " секунд" << std::endl;

    start = std::chrono::high_resolution_clock().now();
    for (int i = 0; i < N; i++) {
        map.find(rs[i]);
    }
    end = std::chrono::high_resolution_clock().now();
    time = std::chrono::duration<double>(end - start).count();
    std::cout << "поиск "<< M <<" строк в std::map занял " << time << " секунд" << std::endl;
}
