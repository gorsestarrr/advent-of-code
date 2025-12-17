cmake_minimum_required(VERSION 4.0)
project(advent_of_code)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE AOC_SOURCES
        "*.cpp"
)

add_executable(advent_of_code
        ${AOC_SOURCES}
)
