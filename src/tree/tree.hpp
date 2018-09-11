#ifndef TREE_H
#define TREE_H

#include <vector>
#include <tuple>
#include <unordered_map>
#include "nodes.hpp"

class Tree
{
  public:
	Tree(std::vector<std::vector<double>> data)
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
	EndNode *classify(std::vector<double> row)
	{
		return _classify(row, root);
	}

  private:
	std::vector<std::vector<double>> data;
	Node *root;

	Node *_build_tree(std::vector<std::vector<double>> rows);
	std::tuple<double, Question *> find_best_split(std::vector<std::vector<double>> rows);
	double gini(std::vector<std::vector<double>> rows);
	std::tuple<std::vector<std::vector<double>>,
			   std::vector<std::vector<double>>>
	partition(std::vector<std::vector<double>> rows,
			  Question *question);
	double info_gain(std::vector<std::vector<double>> left,
					 std::vector<std::vector<double>> right,
					 double current_uncertainty);
	EndNode *_classify(std::vector<double> row, Node *node);
};

#endif
