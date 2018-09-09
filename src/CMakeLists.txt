cmake_minimum_required (VERSION 2.6)
project (random_forest)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_BUILD_TYPE Debug)

include_directories (${PROJECT_SOURCE_DIR}/nodes)
include_directories (${PROJECT_SOURCE_DIR}/tree)
include_directories (${PROJECT_SOURCE_DIR}/forest)

add_executable (
	random_forest.elf
	${PROJECT_SOURCE_DIR}/nodes/nodes.cpp
	${PROJECT_SOURCE_DIR}/tree/tree.cpp
	${PROJECT_SOURCE_DIR}/forest/forest.cpp
	main.cpp
)
