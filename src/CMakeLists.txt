cmake_minimum_required (VERSION 2.6)
project (random_forest)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_BUILD_TYPE Debug)

include_directories (${PROJECT_SOURCE_DIR}/nodes)
include_directories (${PROJECT_SOURCE_DIR}/tree)
include_directories (${PROJECT_SOURCE_DIR}/forest)

add_executable (
	random_forest.elf
	nodes/nodes.cpp
	tree/tree.cpp
	forest/forest.cpp
	main.cpp
)
