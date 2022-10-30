
#include "cppgit/version.hpp"
#include <doctest/doctest.h>
#include <iostream>
#include <string>

TEST_CASE("Greeter version") {
    static_assert(std::string_view(CPPGIT_VERSION) == std::string_view("1.0.0"));
    CHECK(std::string(CPPGIT_VERSION) == std::string("1.0.0"));
}
