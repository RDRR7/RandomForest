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
	bool match(std::vector<int> example);
	const std::string to_string();

  private:
	int column;
	int value;
};

class Node
{
  public:
	Node() {}
	virtual ~Node() {}
	virtual const std::string to_string() = 0;
};

class DecisionNode : public Node
{
  public:
	DecisionNode(Question *question,
				 Node *true_branch,
				 Node *false_branch)
		: question(question),
		  true_branch(true_branch),
		  false_branch(false_branch) {}
	~DecisionNode()
	{
		delete question;
		delete true_branch;
		delete false_branch;
	}
	const std::string to_string() override;

  private:
	Question *question;
	Node *true_branch;
	Node *false_branch;
};

class EndNode : public Node
{
  public:
	EndNode(std::vector<std::vector<int>> data)
		: data(data) {}
	~EndNode() {}
	const std::string to_string() override;

  private:
	std::vector<std::vector<int>> data;
};

#endif
