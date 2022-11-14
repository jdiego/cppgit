#include "cppgit/git2api.hpp"
#include "cppgit/exception.hpp"
#include <git2.h>

namespace cppgit {

Git2API::Git2API() {
    if (++m_init_counter == 1) {
        git_libgit2_init(); 
    }
}

Git2API::Git2API(const Git2API&) {
    ++m_init_counter;
}


Git2API::~Git2API() {
    if (--m_init_counter == 0){
        git_libgit2_shutdown();
    }
}

int Git2API::counter() noexcept{
    return Git2API::m_init_counter;
}
std::tuple<int, int, int> Git2API::version() {
    int major = 0, minor = 0, revision = 0;
    if (git_libgit2_version(&major, &minor, &revision) != 0) {
        //
        throw Exception();
    }
    return {major, minor, revision};
}

} // namespace cppgit
