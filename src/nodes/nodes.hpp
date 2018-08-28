#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

class Question
{
  public:
	Question(int column,
			 int value)
		: column(column),
		  value(value) {}
	int get_column()
	{
		return column;
	}
	int get_value()
	{
		return value;
	}

  private:
	int column;
	int value;
};

class DecisionNode
{
  public:
	DecisionNode(Question *question,
				 DecisionNode *true_branch,
				 DecisionNode *false_branch)
		: question(question),
		  true_branch(true_branch),
		  false_branch(false_branch) {}
	~DecisionNode()
	{
		delete question;
		delete true_branch;
		delete false_branch;
	}

  private:
	Question *question;
	DecisionNode *true_branch;
	DecisionNode *false_branch;
};

class EndNode
{
  public:
	EndNode(std::vector<std::vector<int>> data)
		: data(data) {}

  private:
	std::vector<std::vector<int>> data;
};

#endif
