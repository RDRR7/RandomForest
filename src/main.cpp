#include <iostream>
#include "tree.hpp"

int main(int argc, char *argv[])
{
	/*
	[['Green', 3, 'Apple'],
    ['Yellow', 3, 'Apple'],
    ['Red', 1, 'Grape'],
    ['Red', 1, 'Grape'],
    ['Yellow', 3, 'Lemon']]
	*/
	std::vector<std::vector<int>> data = {{1, 3, 1},
										  {2, 3, 1},
										  {3, 1, 3},
										  {3, 1, 3},
										  {2, 3, 2}};
	Tree tree(data);
	tree.build_tree();
	std::cout << tree.to_string() << std::endl;

	return 0;
}
