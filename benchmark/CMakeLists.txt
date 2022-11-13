cmake_minimum_required(VERSION 3.14...3.22)

set(LIB_NAME ${CMAKE_PROJECT_NAME})
set(BENCH_SUITE ${CMAKE_PROJECT_NAME}-bench)
include (Utils)
message(STATUS "Started ${BENCH_SUITE} Benchmark Suite for ${CMAKE_PROJECT_NAME}...\n")
#
project(${BENCH_SUITE} LANGUAGES CXX)

# ######################################################################################################################
# Options
# ######################################################################################################################
option(USE_BENCH_INSTALLED_VERSION "Benchmarking a version found by find_package" OFF)
option(CPM_USE_LOCAL_PACKAGES "Always try to use `find_package` to get dependencies" TRUE)


# ---- Dependencies ----

include(../cmake/CPM.cmake)

# ######################################################################################################################
# Adding Dependencies
# ######################################################################################################################
find_package(Threads)
CPMAddPackage(
    NAME nanobench
    GITHUB_REPOSITORY martinus/nanobench
    VERSION 4.10
    GIT_TAG v4.1.0
    OPTIONS 
        "GIT_SHALLOW TRUE"
)
CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")

if(USE_BENCH_INSTALLED_VERSION)
    find_package(${LIB_NAME} REQUIRED)
else()
    verbose_message("Adding ${LIB_NAME}.")
    #CPMAddPackage(NAME ${ProjectModule} SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
endif()


# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${BENCH_SUITE} ${sources})
target_link_libraries(${BENCH_SUITE} PRIVATE Threads::Threads nanobench libgit2package)
target_include_directories(
        ${BENCH_SUITE}
        PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${LIBGIT2_INCLUDE_DIR}
    )
set_target_properties(${BENCH_SUITE} PROPERTIES CXX_STANDARD 20)