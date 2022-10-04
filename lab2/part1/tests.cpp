#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <vector>
#include <algorithm>
#include "../../catch.hpp"
#include "count_sort.h"


std::vector<int> mas0_15{3, 1, 5, 0, 2, 2, 14, 11, 10, 9, 12, 5, 12, 7};
std::vector<int> mas5_20{16, 5, 7,11, 8, 19, 16 ,12};
std::vector<int> without_elems;
std::vector<int> masn5_5{4, 3, 2, 1, 0, -1, -2, -3, -4, -5};
std::vector<int> identical_elems{1, 1, 1, 1, 1, 1, 1, 1, 1};


TEST_CASE("0 ... 15", "test") {
    std::vector<int> res{0, 1, 2, 2, 3, 5, 5, 7, 9, 10, 11, 12, 12, 14};
    std::vector<int> actual_res(mas0_15);
    count_sort(actual_res, 0, 15);
    for (int i{0}; i < res.size(); i++) {
        REQUIRE(res[i] == actual_res[i]);
    }
}

TEST_CASE("5 ... 20", "test") {
    std::vector<int> res{5, 7, 8, 11, 12, 16, 16, 19};
    std::vector<int> actual_res(mas5_20);
    count_sort(actual_res, 5, 20);
    for (int i{0}; i < res.size(); i++) {
        REQUIRE(res[i] == actual_res[i]);
    }
}


TEST_CASE("-5 ... 5", "test") {
    std::vector<int> res{-5, -4, -3, -2, -1, 0, 1, 2, 3, 4};
    std::vector<int> actual_res(masn5_5);
    count_sort(actual_res, -5, 5);
    for (int i{0}; i < res.size(); i++) {
        REQUIRE(res[i] == actual_res[i]);
    }
}

TEST_CASE("no elements", "test") {
    std::vector<int> actual_res(without_elems);
    count_sort(actual_res, -5, 5);
    REQUIRE(actual_res.size() == 0);
}

TEST_CASE("identical elements", "test") {
    std::vector<int> res{1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::vector<int> actual_res(identical_elems);
    count_sort(actual_res, -5, 5);
    for (int i{0}; i < res.size(); i++) {
        REQUIRE(res[i] == actual_res[i]);
    }
}