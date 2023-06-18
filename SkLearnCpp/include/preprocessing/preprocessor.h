#pragma once
#include <vector>

class Preprocessor
{
public:
	virtual ~Preprocessor() {};
	virtual void fit(const std::vector<std::vector<double>>& data) = 0;
	virtual std::vector<std::vector<double>> transform(const std::vector<std::vector<double>>& data) const = 0;
	virtual std::vector<std::vector<double>> fit_transform(const std::vector<std::vector<double>>& data) = 0;
	virtual std::vector<std::vector<double>> inverse_transform(const std::vector<std::vector<double>>& data) const = 0;
};

class StandardScaler : public Preprocessor {
public:
	~StandardScaler();
	void fit(const std::vector<std::vector<double>>& data) override;
	std::vector<std::vector<double>> fit_transform(const std::vector<std::vector<double>>& data) override;
	std::vector<std::vector<double>> transform(const std::vector<std::vector<double>>& data) const override;
	std::vector<std::vector<double>> inverse_transform(const std::vector<std::vector<double>>& data) const override;

private:
	std::vector<double> means;
	std::vector<double> stds;
};

class MinMaxScaler : public Preprocessor {
public:
	MinMaxScaler();
	~MinMaxScaler();
	void fit(const std::vector<std::vector<double>>& data) override;
	std::vector<std::vector<double>> fit_transform(const std::vector<std::vector<double>>& data) override;
	std::vector<std::vector<double>> transform(const std::vector<std::vector<double>>& data) const override;
	std::vector<std::vector<double>> inverse_transform(const std::vector<std::vector<double>>& data) const override;

private:
	std::vector<double> dataMin;
	std::vector<double> dataMax;
	std::pair<double, double> featureRange;
};