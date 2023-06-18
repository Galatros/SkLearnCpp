#pragma once
#include <vector>

class Classifier {
public:
	//virtual ~Classifier() {}
	virtual void fit(const std::vector<std::vector<double>>& X_train, const std::vector<int>& y_train) = 0;
	virtual int predict(std::vector<double> point)= 0;
	virtual std::vector<int> predict(std::vector<std::vector<double>> points) = 0;
};
