#include "nodes.hpp"
#include <set>
#include <iostream>
#include <iomanip>
#include <unordered_map>

bool Question::match(std::vector<double> example)
{
	return example[column] >= value;
}

const std::string Question::to_string()
{
	std::string question_str = "Is column [ ";
	question_str += std::to_string(column);
	question_str += " ] >= ";
	question_str += std::to_string(value);
	question_str += "\n";
	return question_str;
}

const std::string DecisionNode::to_string()
{
	std::string decision_node_str = "";
	decision_node_str += question->to_string();
	decision_node_str += "true\n";
	decision_node_str += true_branch->to_string();
	decision_node_str += "false\n";
	decision_node_str += false_branch->to_string();
	return decision_node_str;
}

const std::string EndNode::to_string()
{
	std::string end_node_str = "predict {";

	std::set<double> values;
	for (auto row : data)
	{
		values.insert(row.back());
	}

	bool first = true;
	for (auto label : values)
	{
		if (first)
		{
			first = false;
			end_node_str += " [ ";
		}
		else
		{
			end_node_str += ", [ ";
		}
		end_node_str += std::to_string(label);
		end_node_str += " ]: ";
		int count = 0;
		for (int i = 0; i < data.size(); i++)
		{
			if (data[i].back() == label)
			{
				count++;
			}
		}
		end_node_str += std::to_string(count);
	}

	end_node_str += " }\n";
	return end_node_str;
}

void EndNode::print_classification()
{
	double total = 0;
	std::set<double> values;
	for (auto row : data)
	{
		total++;
		values.insert(row.back());
	}

	bool first = true;
	for (auto label : values)
	{
		if (first)
		{
			first = false;
			std::cout << "[ ";
		}
		else
		{
			std::cout << ", [ ";
		}
		std::cout << std::fixed;
		std::cout << std::setprecision(0);
		std::cout << label;
		std::cout << " ]: ";
		int count = 0;
		for (int i = 0; i < data.size(); i++)
		{
			if (data[i].back() == label)
			{
				count++;
			}
		}
		std::cout << std::fixed;
		std::cout << std::setprecision(2);
		std::cout << (double)count / total * 100;
		std::cout << "% ";
	}
	std::cout << std::endl;
}

double EndNode::classify()
{
	double highest_label = 0;
	int highest_value = 0;
	std::unordered_map<double, int> values;
	for (auto row : data)
	{
		values[row.back()]++;
	}
	for (auto label_count : values)
	{
		if (label_count.second > highest_value)
		{
			highest_label = label_count.first;
			highest_value = label_count.second;
		}
		if (label_count.second == highest_value)
		{
			if (std::rand() % 1)
			{
				highest_label = label_count.first;
				highest_value = label_count.second;
			}
		}
	}
	return highest_label;
}
