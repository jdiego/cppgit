#ifndef CPPGIT_GLOBAL_HPP
#define CPPGIT_GLOBAL_HPP

#include <git2-cpp/exception.hpp>
#include <git2/global.h>
#include <mutex>

namespace cppgit {

namespace detail {
void init() {
    git2_throw(git_libgit2_init());
}
} // namespace detail

inline std::once_flag once;

void init() {
    std::call_once(once, detail::init);
}
} // end namespace cppgit

#endif // !CPPGIT_GLOBAL_HPP
