cmake_minimum_required (VERSION 2.6)
project (random_forest)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_BUILD_TYPE Debug)

include_directories (${PROJECT_SOURCE_DIR})
include_directories (${CMAKE_CURRENT_BINARY_DIR})

add_executable (
	random_forest.elf
	main.cpp
)
