#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

enum class NodeType
{
	DECISIONNODE = 1,
	ENDNODE = 2,
};

class Question
{
  public:
	Question(int column,
			 double value)
		: column(column),
		  value(value) {}
	int get_column()
	{
		return column;
	}
	double get_value()
	{
		return value;
	}
	bool match(std::vector<double> example);
	const std::string to_string();

  private:
	int column;
	double value;
};

class Node
{
  public:
	Node(NodeType type)
		: type(type) {}
	virtual ~Node() {}
	virtual const std::string to_string() = 0;
	NodeType get_type()
	{
		return type;
	}

  private:
	NodeType type;
};

class DecisionNode : public Node
{
  public:
	DecisionNode(Question *question,
				 Node *true_branch,
				 Node *false_branch)
		: Node(NodeType::DECISIONNODE),
		  question(question),
		  true_branch(true_branch),
		  false_branch(false_branch) {}
	~DecisionNode()
	{
		delete question;
		delete true_branch;
		delete false_branch;
	}
	const std::string to_string() override;
	Question *get_question()
	{
		return question;
	}
	Node *get_true_branch()
	{
		return true_branch;
	}
	Node *get_false_branch()
	{
		return false_branch;
	}

  private:
	Question *question;
	Node *true_branch;
	Node *false_branch;
};

class EndNode : public Node
{
  public:
	EndNode(std::vector<std::vector<double>> data)
		: Node(NodeType::ENDNODE),
		  data(data) {}
	~EndNode() {}
	const std::string to_string() override;
	std::vector<std::vector<double>> get_data()
	{
		return data;
	}
	void print_classification();
	double classify();

  private:
	std::vector<std::vector<double>> data;
};

#endif
