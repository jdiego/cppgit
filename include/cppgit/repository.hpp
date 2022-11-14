#ifndef CPPGIT_HPP
#define CPPGIT_HPP

#include "cppgit/git2api.hpp"
#include <git2/types.h>
#include <memory>
#include <string>
#include <optional>


namespace cppgit {
    
    enum class branch_type
    {
        LOCAL,
        REMOTE,
        ALL
    };

// =====================================================================================
//        Class:  Repository
//  Description:
//
// =====================================================================================
class Repository: private Git2API {
public:
    // ====================  LIFECYCLE     =======================================
    Repository(std::string_view path, bool is_bare);
    // ====================  ACCESSORS     =======================================
    [[nodiscard]] bool is_bare() const;
    [[nodiscard]] const char* path() const;
    [[nodiscard]] const char* workdir() const;
    [[nodiscard]] static std::optional<std::string> discover_path(std::string_view start_path, bool across_fs = false, std::string_view ceiling_dirs = "");
    // ====================  MUTATORS      =======================================

    // ====================  OPERATORS     =======================================

protected:
    // ====================  METHODS       =======================================

    // ====================  DATA MEMBERS  =======================================

private:
    // ====================  METHODS       =======================================

    // ====================  DATA MEMBERS  =======================================
    struct Destroy { void operator() (git_repository *) const; };
    std::unique_ptr<git_repository, Destroy> m_repo;
}; // -----  end of class Repository  -----
} // namespace cppgit

#endif /* ifndef CPPGIT_HPP */
