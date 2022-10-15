#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include <vector>
#include <algorithm>
#include "../../catch.hpp"
#include "algorithms.h"

std::vector<int> common_numbers = {2, 2, 2 ,4, 1 ,3 ,5, 3, 4, 4, 4};
std::vector<int> identical_numbers = {1, 1, 1, 1, 1, 1, 1, 1, 1};
std::vector<int> no_numbers;
std::vector<int> no_duplicate_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};

TEST_CASE( "common values, has_d, [std::sort]", "[std::sort]" ) {
    REQUIRE(has_duplicates(common_numbers) == true);
}

TEST_CASE( "common values, has_d, [naive]", "[naive]" ) {
    REQUIRE(has_duplicates_naive(common_numbers) == true);
}

TEST_CASE( "identical values, has_d, [std::sort]", "[std::sort]" ) {
    REQUIRE(has_duplicates(identical_numbers) == true);
}

TEST_CASE( "identical values, has_d, [naive]", "[naive]" ) {
    REQUIRE(has_duplicates_naive(identical_numbers) == true);
}

TEST_CASE( "no values, has_d, [std::sort]", "[std::sort]" ) {
    REQUIRE(has_duplicates(no_numbers) == false);
}

TEST_CASE( "no values, has_d, [naive]", "[naive]" ) {
    REQUIRE(has_duplicates_naive(no_numbers) == false);
}

TEST_CASE( "no duplicates, has_d, [std::sort]", "[std::sort]" ) {
    REQUIRE(has_duplicates(no_duplicate_numbers) == false);
}

TEST_CASE( "no duplicates, has_d, [naive]", "[naive]" ) {
    REQUIRE(has_duplicates_naive(no_duplicate_numbers) == false);
}

TEST_CASE("common values, get_d, [std::sort]", "[std::sort]") {
    std::vector<int> my_res = get_duplicates(common_numbers);
    std::vector<int> duplicates = {2, 3, 4};
    REQUIRE(my_res.size() == duplicates.size());
    for (int i = 0; i < my_res.size(); i++) {
        REQUIRE(my_res[i] == duplicates[i]);
    }
    
}

TEST_CASE("common values, get_d", "[naive]") {
    std::vector<int> my_res = get_duplicates_naive(common_numbers);
    std::sort(my_res.begin(), my_res.end());
    std::vector<int> duplicates = {2, 3, 4};
    REQUIRE(my_res.size() == duplicates.size());
    for (int i = 0; i < my_res.size(); i++) {
        REQUIRE(my_res[i] == duplicates[i]);
    }
    
}

TEST_CASE("identical values, get_d, [std::sort]", "[std::sort]") {
    std::vector<int> my_res = get_duplicates(identical_numbers);
    std::vector<int> duplicates = {1};
    REQUIRE(my_res.size() == duplicates.size());
    for (int i = 0; i < my_res.size(); i++) {
        REQUIRE(my_res[i] == duplicates[i]);
    }
    
}

TEST_CASE("identical values, get_d", "[naive]") {
    std::vector<int> my_res = get_duplicates_naive(identical_numbers);
    std::sort(my_res.begin(), my_res.end());
    std::vector<int> duplicates = {1};
    REQUIRE(my_res.size() == duplicates.size());
    for (int i = 0; i < my_res.size(); i++) {
        REQUIRE(my_res[i] == duplicates[i]);
    }
    
}

TEST_CASE("no values, get_d, [std::sort]", "[std::sort]") {
    std::vector<int> my_res = get_duplicates(no_numbers);
    std::vector<int> duplicates = {};
    REQUIRE(my_res.size() == duplicates.size());
    for (int i = 0; i < my_res.size(); i++) {
        REQUIRE(my_res[i] == duplicates[i]);
    }
    
}

TEST_CASE("no values, get_d", "[naive]") {
    std::vector<int> my_res = get_duplicates_naive(no_numbers);
    std::sort(my_res.begin(), my_res.end());
    std::vector<int> duplicates = {};
    REQUIRE(my_res.size() == duplicates.size());
    for (int i = 0; i < my_res.size(); i++) {
        REQUIRE(my_res[i] == duplicates[i]);
    }
    
}

TEST_CASE("no duplicate values, get_d, [std::sort]", "[std::sort]") {
    std::vector<int> my_res = get_duplicates(no_duplicate_numbers);
    std::vector<int> duplicates = {};
    REQUIRE(my_res.size() == duplicates.size());
    for (int i = 0; i < my_res.size(); i++) {
        REQUIRE(my_res[i] == duplicates[i]);
    }
    
}

TEST_CASE("no duplicate values, get_d", "[naive]") {
    std::vector<int> my_res = get_duplicates_naive(no_duplicate_numbers);
    std::sort(my_res.begin(), my_res.end());
    std::vector<int> duplicates = {};
    REQUIRE(my_res.size() == duplicates.size());
    for (int i = 0; i < my_res.size(); i++) {
        REQUIRE(my_res[i] == duplicates[i]);
    }
    
}