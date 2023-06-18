#pragma once
#include <unordered_map>
#include <string>

class LabelEncoder {
public:
	void fit(const std::vector<std::string>& labels);
	std::vector<int> transform(const std::vector<std::string>& labels) const;
	std::vector<std::string> inverse_transform(const std::vector<int>& encodedLabels) const;
	std::vector<int> fit_transform(const std::vector<std::string>& labels);

private:
	std::unordered_map<std::string, int> indexMap;
};