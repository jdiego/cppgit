
#include "cppgit/git2api.hpp"
#include "cppgit/version.hpp"
#include <doctest/doctest.h>
#include <iostream>
#include <string>

class Object: private cppgit::Git2API {

};

TEST_CASE("Version") {
    static_assert(std::string_view(CPPGIT_VERSION) == std::string_view("1.0.0"));
    CHECK(std::string(CPPGIT_VERSION) == std::string("1.0.0"));
}

TEST_CASE("Initialization Test") {
    {
        const cppgit::Git2API git_obj1;
        {
            const cppgit::Git2API git_obj2;
            const Object git_obj3;
            CHECK(cppgit::Git2API::counter() == 3);
        }
        CHECK(cppgit::Git2API::counter() == 1);
        const cppgit::Git2API git_obj2;
        CHECK(cppgit::Git2API::counter() == 2);
    }
    CHECK(cppgit::Git2API::counter() == 0);

}
