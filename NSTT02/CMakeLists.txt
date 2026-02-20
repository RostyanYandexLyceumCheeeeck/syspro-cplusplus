cmake_minimum_required(VERSION 3.27)
project(NSTT2)

enable_testing()

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -O1 -ggdb")

add_subdirectory(src)
add_subdirectory(test)

include_directories(src)