#include <nanobench.h>
#include <git2.h>
#include <random>

void init_n_times(int n){
    for (int i =0; i < n; ++i) 
    {
        git_libgit2_init();
        git_libgit2_shutdown();
    }
}
void init(){
    git_libgit2_init();
    git_libgit2_shutdown();
}

void init_atomic_n_times(int n){
    std::atomic<int> counter { 0};
    for (int i =0; i < n; ++i) 
    {
        if (counter == 0) {
            git_libgit2_init();
            git_libgit2_shutdown();
        }
        ++counter;
    }
}
int main() {
    ankerl::nanobench::Bench().epochs(10).run("test git initialization", [&] {
        init();
    });

    ankerl::nanobench::Bench().epochs(10).run("test git initialization n times", [&] {
        init_n_times(10);
    });
    ankerl::nanobench::Bench().epochs(10).run("test git initialization with atomic", [&] {
        init_atomic_n_times(10); 
    });
}
