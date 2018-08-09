cmake_minimum_required(VERSION 2.6)
project(rngharness)

add_executable(rngharness main.cpp)

install(TARGETS rngharness RUNTIME DESTINATION bin)
