#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../../catch.hpp"
#include "dictionary.h"

TEST_CASE("dictionary(1)", "set && get") {
    Dictionary d(HashFunc::hash1);
    d.set("ac", "sum a + c");
    d.set("bb", "sum b + b");
    REQUIRE("sum a + c" == d.get("ac").value);
    REQUIRE("sum b + b" == d.get("bb").value);
    REQUIRE(false == d.get("not in hash map").res);
    
}

TEST_CASE("dictionary(2)", "set && get") {
    Dictionary d(HashFunc::hash2);
    d.set("ac", "1898 letters"); // (97 + 99 ^ 2) % 2000 = 1898
    d.set("1+", "1898 1+"); // 49 + 43 ^ 2 = 1898
    REQUIRE("1898 letters" == d.get("ac").value);
    REQUIRE("1898 1+" == d.get("1+").value);
    REQUIRE(false == d.get("not in hash map").res);
    
}

TEST_CASE("dictionary(3)", "set && get") {
    Dictionary d(HashFunc::shift);
    d.set("ac", "sum a + c");
    d.set("bb", "sum b + b");
    REQUIRE("sum a + c" == d.get("ac").value);
    REQUIRE("sum b + b" == d.get("bb").value);
    REQUIRE(false == d.get("not in hash map").res);
}