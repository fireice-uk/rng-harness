cmake_minimum_required(VERSION 2.6)
project(rngharness)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Threads REQUIRED)

add_executable(rngharness main.cpp keccak.c)
target_link_libraries(rngharness Threads::Threads)
install(TARGETS rngharness RUNTIME DESTINATION bin)
