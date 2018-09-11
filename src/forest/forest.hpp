#ifndef FOREST_H
#define FOREST_H

#include <vector>
#include "tree.hpp"

class Forest
{
  public:
	Forest(std::vector<std::vector<double>> data, int forest_size);
	~Forest();
	double classify(std::vector<double> row);
	double calculate_precision();
	double calculate_error();

  private:
	int forest_size;
	std::vector<Tree *> trees;
	std::vector<std::vector<double>> test_data;
};

#endif
