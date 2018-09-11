#include "tree.hpp"
#include <set>

Node *Tree::_build_tree(std::vector<std::vector<double>> rows)
{
	std::tuple<double, Question *> gain_and_question = find_best_split(rows);
	int gain = std::get<0>(gain_and_question);
	Question *question = std::get<1>(gain_and_question);

	if (gain == 0)
	{
		return new EndNode(rows);
	}

	std::tuple<std::vector<std::vector<double>>,
			   std::vector<std::vector<double>>>
		true_and_false_rows = partition(rows, question);

	std::vector<std::vector<double>> true_rows =
		std::get<0>(true_and_false_rows);
	std::vector<std::vector<double>> false_rows =
		std::get<1>(true_and_false_rows);

	Node *true_branch = _build_tree(true_rows);
	Node *false_branch = _build_tree(false_rows);

	return new DecisionNode(question, true_branch, false_branch);
}

std::unordered_map<int, int> class_counts(std::vector<std::vector<double>> rows)
{
	std::unordered_map<int, int> counts;
	for (auto row : rows)
	{
		int label = row.back();
		counts[label]++;
	}
	return counts;
}

double Tree::gini(std::vector<std::vector<double>> rows)
{
	std::unordered_map<int, int> counts = class_counts(rows);
	double impurity = 1;
	for (const auto &label : counts)
	{
		double probability_of_label = label.second / rows.size();
		impurity -= probability_of_label * probability_of_label;
	}
	return impurity;
}

std::tuple<std::vector<std::vector<double>>,
		   std::vector<std::vector<double>>>
Tree::partition(std::vector<std::vector<double>> rows,
				Question *question)
{
	std::vector<std::vector<double>> true_rows;
	std::vector<std::vector<double>> false_rows;

	for (auto row : rows)
	{
		if (question->match(row))
		{
			true_rows.push_back(row);
		}
		else
		{
			false_rows.push_back(row);
		}
	}

	return std::make_tuple(true_rows, false_rows);
}

double Tree::info_gain(std::vector<std::vector<double>> left,
					   std::vector<std::vector<double>> right,
					   double current_uncertainty)
{
	double p = left.size() / (left.size() + right.size());
	return current_uncertainty - p * gini(left) - (1 - p) * gini(right);
}

std::tuple<double, Question *> Tree::find_best_split(std::vector<std::vector<double>> rows)
{
	int best_gain = 0;
	Question *best_question;
	double current_uncertainty = gini(rows);
	int n_features = rows[0].size() - 1;

	for (int column = 0; column < n_features; column++)
	{
		std::set<double> values;
		for (auto row : rows)
		{
			values.insert(row[column]);
		}
		for (auto value : values)
		{
			Question *question = new Question(column, value);
			std::tuple<std::vector<std::vector<double>>,
					   std::vector<std::vector<double>>>
				true_and_false_rows = partition(rows, question);

			std::vector<std::vector<double>> true_rows =
				std::get<0>(true_and_false_rows);
			std::vector<std::vector<double>> false_rows =
				std::get<1>(true_and_false_rows);

			if (true_rows.empty() || false_rows.empty())
			{
				delete question;
				continue;
			}

			double gain = info_gain(true_rows, false_rows, current_uncertainty);
			if (gain >= best_gain)
			{
				best_gain = gain;
				best_question = question;
			}
			else
			{
				delete question;
			}
		}
	}
	return std::make_tuple(best_gain, best_question);
}

const std::string Tree::to_string()
{
	std::string tree_str = "";
	tree_str += root->to_string();
	return tree_str;
}

EndNode *Tree::_classify(std::vector<double> row, Node *node)
{
	if (node->get_type() == NodeType::ENDNODE)
	{
		return static_cast<EndNode *>(node);
	}

	DecisionNode *decision_node = static_cast<DecisionNode *>(node);

	if (decision_node->get_question()->match(row))
	{
		return _classify(row, decision_node->get_true_branch());
	}
	else
	{
		return _classify(row, decision_node->get_false_branch());
	}
}
