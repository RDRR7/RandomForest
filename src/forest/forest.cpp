#include "forest.hpp"
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <cassert>

Forest::Forest(std::vector<std::vector<double>> data, int forest_size)
{
	std::random_shuffle(data.begin(), data.end());

	std::size_t train_size = data.size() * 0.80;
	assert(forest_size <= train_size);

	std::vector<std::vector<double>> train_data(data.begin(), data.begin() + train_size);
	test_data = std::vector<std::vector<double>>(data.begin() + train_size, data.end());

	std::unordered_map<int, std::vector<std::vector<double>>> partitions;
	int i = 0;
	for (auto line : train_data)
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

double Forest::calculate_precision()
{
	int count = 0;
	for (auto entry : test_data)
	{
		if (classify(entry) == entry.back())
		{
			count++;
		}
	}
	return count / static_cast<double>(test_data.size()) * 100;
}

double Forest::calculate_error()
{
	int count = 0;
	for (auto entry : test_data)
	{
		if (classify(entry) == entry.back())
		{
			count++;
		}
	}
	return (1 - (count / static_cast<double>(test_data.size()))) * 100;
}
