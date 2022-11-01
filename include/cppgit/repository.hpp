#ifndef CPPGIT_HPP
#define CPPGIT_HPP

#include <tuple>

namespace cppgit {
// =====================================================================================
//        Class:  Repository
//  Description:
//
// =====================================================================================
class Repository {
public:
    // ====================  LIFECYCLE     =======================================
    Repository() = default;
    // ====================  ACCESSORS     =======================================
    std::tuple<int, int, int> version() const;
    // ====================  MUTATORS      =======================================

    // ====================  OPERATORS     =======================================

protected:
    // ====================  METHODS       =======================================

    // ====================  DATA MEMBERS  =======================================

private:
    // ====================  METHODS       =======================================

    // ====================  DATA MEMBERS  =======================================

}; // -----  end of class Repository  -----
} // namespace cppgit

#endif /* ifndef CPPGIT_HPP */
