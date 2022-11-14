#ifndef CPPGIT_GIT2API_HPP
#define CPPGIT_GIT2API_HPP

#include <tuple>
#include <atomic>
namespace cppgit {
// =====================================================================================
//        Class:  Git
//  Description:
// =====================================================================================
class Git2API {
public:
    // ====================  LIFECYCLE     =======================================
    Git2API();
    Git2API(const Git2API &);
    Git2API(Git2API &&) = delete;
    Git2API &operator=(const Git2API &) = default;
    Git2API &operator=(Git2API &&) = delete;
    virtual ~Git2API();
    // ====================  ACCESSORS     =======================================
    [[nodiscard]] static int counter() noexcept;
    [[nodiscard]] static std::tuple<int, int, int> version();
    // ====================  MUTATORS      =======================================
    // ====================  OPERATORS     =======================================
protected:
    // ====================  METHODS       =======================================
    // ====================  DATA MEMBERS  =======================================
private:
    // ====================  METHODS       =======================================
    // ====================  DATA MEMBERS  =======================================
    inline static std::atomic<int> m_init_counter{0};
}; // -----  end of class Git2API  -----
} // namespace cppgit

#endif
