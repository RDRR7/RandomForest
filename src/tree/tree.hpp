#ifndef TREE_H
#define TREE_H

#include <vector>
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

  private:
	std::vector<std::vector<int>> data;
	DecisionNode *root;

	DecisionNode *_build_tree(std::vector<std::vector<int>> data);
};

#endif
