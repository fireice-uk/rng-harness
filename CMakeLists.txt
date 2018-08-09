cmake_minimum_required(VERSION 2.6)
project(rngharness)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(test test.cpp)
target_link_libraries(test Threads::Threads)

add_executable(rngharness main.cpp)

install(TARGETS rngharness RUNTIME DESTINATION bin)
