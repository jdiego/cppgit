#ifndef CPPGIT_EXCEPTION_HPP
#define CPPGIT_EXCEPTION_HPP

#include <exception>
#include <git2.h>
#include <string>

namespace cppgit {

class Exception : public std::exception {
public:
    // ====================  LIFECYCLE     =======================================
    Exception();
    explicit Exception(std::string_view message);
    Exception(const Exception &) = default;
    Exception &operator=(const Exception &) = delete;
    Exception(Exception &&) = default;
    Exception &operator=(Exception &&) = delete;
    ~Exception() noexcept override = default;
    //
    [[nodiscard]] const char *what() const noexcept override {
        return this->m_message.c_str();
    }
    // ====================  ACCESSORS     =======================================
    [[nodiscard]] git_error_t category() const noexcept {
        return this->m_category;
    }

private:
    // ====================  METHODS       =======================================
    static int git2_throw(int ret);
    // ====================  DATA MEMBERS  =======================================
    std::string m_message;
    git_error_t m_category;
}; // -----  end of class Exception -----

} // namespace cppgit

#endif
