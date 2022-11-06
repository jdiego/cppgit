#include "cppgit/git.hpp"
#include <git2.h>

namespace cppgit {

Git::Git() {
    git_libgit2_init();
}

Git::~Git() {
    git_libgit2_shutdown();
}
std::tuple<int, int, int> Git::version() {
    int major = 0, minor = 0, revision = 0;
    if (git_libgit2_version(&major, &minor, &revision) != 0) {
        //
    }
    return {major, minor, revision};
}

} // namespace cppgit
