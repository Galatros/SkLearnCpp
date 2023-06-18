#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include "../../include/algorithms/knn.h"

void plotDecisionRegions(const std::vector<std::vector<double>>& X, const std::vector<int>& y, const std::vector<std::vector<double>>& X_test, const std::vector<int>& y_test, Classifier& classifier);
