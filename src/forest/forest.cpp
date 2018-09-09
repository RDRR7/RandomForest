#include "forest.hpp"
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <cassert>

Forest::Forest(std::vector<std::vector<double>> data, int forest_size)
{
	assert(forest_size <= data.size());
	std::random_shuffle(data.begin(), data.end());
	std::unordered_map<int, std::vector<std::vector<double>>> partitions;

	int i = 0;
	for (auto line : data)
	{
		partitions[i].push_back(line);
		i++;
		if (i >= forest_size)
		{
			i = 0;
		}
	}

	for (i = 0; i < forest_size; i++)
	{
		trees.push_back(new Tree(partitions[i]));
		trees.back()->build_tree();
	}
}

Forest::~Forest()
{
	for (auto tree : trees)
	{
		delete tree;
	}
	trees.clear();
}

double Forest::classify(std::vector<double> row)
{
	std::unordered_map<double, double> classification;
	for (auto tree : trees)
	{
		classification[tree->classify(row)->classify()]++;
	}

	double highest_label = 0;
	int highest_value = 0;
	for (auto label : classification)
	{
		if (label.second > highest_value)
		{
			highest_label = label.first;
			highest_value = label.second;
		}
		if (label.second == highest_value)
		{
			if (std::rand() % 1)
			{
				highest_label = label.first;
				highest_value = label.second;
			}
		}
	}
	return highest_label;
}
