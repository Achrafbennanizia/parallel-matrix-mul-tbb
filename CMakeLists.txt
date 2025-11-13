cmake_minimum_required(VERSION 3.15)
project(parallel_matrix_mul_tbb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Homebrew TBB Pfade (macOS) ----
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(matrix_mul src/main.cpp)

target_link_libraries(matrix_mul PRIVATE tbb)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
