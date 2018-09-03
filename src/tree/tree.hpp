#ifndef TREE_H
#define TREE_H

#include <vector>
#include <tuple>
#include <map>
#include "nodes.hpp"

class Tree
{
  public:
	Tree(std::vector<std::vector<int>> data)
		: data(data) {}
	~Tree()
	{
		delete root;
	}
	void build_tree()
	{
		root = _build_tree(data);
	}
	const std::string to_string();

  private:
	std::vector<std::vector<int>> data;
	Node *root;

	Node *_build_tree(std::vector<std::vector<int>> rows);
	std::tuple<int, Question *> find_best_split(std::vector<std::vector<int>> rows);
	double gini(std::vector<std::vector<int>> rows);
	std::tuple<std::vector<std::vector<int>>,
			   std::vector<std::vector<int>>>
	partition(std::vector<std::vector<int>> rows,
			  Question *question);
	double info_gain(std::vector<std::vector<int>> left,
					 std::vector<std::vector<int>> right,
					 double current_uncertainty);
};

#endif
