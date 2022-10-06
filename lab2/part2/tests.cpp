#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "../../catch.hpp"
#include "dictionary.h"

TEST_CASE("dictionary(1)", "set") {
    Dictionary d(1);
    d.set("ac", "sum a + c");
    d.set("bb", "sum b + b");
    REQUIRE("sum a + c" == d.get("ac").value);
    REQUIRE("sum b + b" == d.get("bb").value);
}