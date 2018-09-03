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
	std::cout << tree.to_string() << std::endl;

	std::vector<int> test1 = {1, 3, 1};
	std::vector<int> test2 = {2, 4, 1};
	std::vector<int> test3 = {3, 2, 3};
	std::vector<int> test4 = {3, 1, 3};
	std::vector<int> test5 = {2, 3, 2};

	tree.classify(test1)->print_classification();
	tree.classify(test2)->print_classification();
	tree.classify(test3)->print_classification();
	tree.classify(test4)->print_classification();
	tree.classify(test5)->print_classification();

	return 0;
}
