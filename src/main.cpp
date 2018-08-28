#include <iostream>
#include "tree.hpp"

int main(int argc, char *argv[])
{
	std::vector<std::vector<int>> data = {{1, 3, 1},
										  {2, 3, 1},
										  {3, 1, 3},
										  {3, 1, 3},
										  {2, 3, 2}};
	Tree tree(data);
	tree.build_tree();
	return 0;
}
