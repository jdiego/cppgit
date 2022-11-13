#include "cppgit/exception.hpp"
#include <git2.h>

namespace cppgit {

Exception::Exception() {
    if (const auto *error = git_error_last(); error != nullptr) {
        this->m_message += error->message;
        this->m_category = static_cast<git_error_t>(error->klass);
        git_error_clear();
    }
}

int Exception::git2_throw(int ret) {
    if (ret < 0) {
        throw Exception();
    }
    return ret;
}

} // namespace cppgit
