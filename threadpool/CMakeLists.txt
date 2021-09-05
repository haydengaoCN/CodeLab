cmake_minimum_required(VERSION 3.17)
project (thread-pool)

set(HEADERS src/thread_pool.h src/safe_queue.h)
set(SOURCES tests/main.cc)

set(CMAKE_CXX_FLAGS -pthread)

add_compile_options(
  -std=c++14
  -I/data/home/haydengao/code_lab/
)

add_executable(test ${HEADERS} ${SOURCES})
target_link_libraries(test)