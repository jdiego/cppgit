#include "cppgit/repository.hpp"
#include "cppgit/exception.hpp"
#include <git2.h>

namespace cppgit {
    Repository::Repository(std::string_view path, bool is_bare){
        git_repository* repo = nullptr;
        if (git_repository_init(&repo, path.data(), static_cast<unsigned int>(is_bare)) != 0) {
            throw Exception();
        }
        m_repo.reset(repo);
    }
    
    void Repository::Destroy::operator() (git_repository* repo) const
    {
        git_repository_free(repo);
    }

    bool Repository::is_bare() const {
        return git_repository_is_bare(m_repo.get()) != 0;
    }
    
    const char* Repository::path() const
    {
        return git_repository_path(m_repo.get());
    }
    const char* Repository::workdir() const
    {
        return git_repository_workdir(m_repo.get());
    }
    
    std::optional<std::string> Repository::discover_path(std::string_view start_path, bool across_fs, std::string_view ceiling_dirs) {
        git_buf buffer = {.ptr = nullptr, .size = 0};
        if (git_repository_discover(&buffer, start_path.data(), static_cast<int>(across_fs), ceiling_dirs.data()) != 0) {
            return std::nullopt;
        }
        return std::string(buffer.ptr, buffer.size);
    }
}
