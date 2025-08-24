cmake_minimum_required(VERSION 3.16)
project(HybridAStarFrontiers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_BENCHMARKS "Build benchmarks" ON)

add_library(frontier INTERFACE)
target_include_directories(frontier INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(frontier INTERFACE cxx_std_20)

add_executable(hybrid-a-star-frontiers src/main.cpp)
target_link_libraries(hybrid-a-star-frontiers PRIVATE frontier)
target_compile_options(hybrid-a-star-frontiers PRIVATE -Wall -Wextra -Wpedantic -Werror)

if(BUILD_TESTS)
  enable_testing()
  add_executable(test_minimal tests/test_minimal.cpp)
  target_link_libraries(test_minimal PRIVATE frontier)
  target_compile_options(test_minimal PRIVATE -Wall -Wextra -Wpedantic -Werror)
  add_test(NAME MinimalTest COMMAND test_minimal)

  add_executable(test_bucket_heap tests/test_bucket_heap.cpp)
  target_link_libraries(test_bucket_heap PRIVATE frontier)
  target_compile_options(test_bucket_heap PRIVATE -Wall -Wextra -Wpedantic -Werror)
  add_test(NAME BucketHeapTest COMMAND test_bucket_heap)
endif()

if(BUILD_BENCHMARKS)
  add_executable(frontier_bench benchmarks/frontier_bench.cpp)
  target_link_libraries(frontier_bench PRIVATE frontier)
  target_compile_options(frontier_bench PRIVATE -Wall -Wextra -Wpedantic)
endif()
