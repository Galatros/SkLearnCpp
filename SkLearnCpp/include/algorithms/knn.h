#pragma once
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

class Classifier {
public:
	virtual ~Classifier() {}
	virtual void fit(const std::vector<std::vector<double>>& X_train, const std::vector<int>& y_train) = 0;
	virtual int predict(std::vector<double> point) const = 0;
	virtual std::vector<int> predict(std::vector<std::vector<double>> points) const = 0;
};


class KNN : public Classifier
{
private:
	std::vector<std::vector<double>> X_train; //macierz danych treningowych
	std::vector<int> y_train; //etykiety danych treningowych
	int k; //liczba najblizszych sasiadow

	double euclideanDistance(const std::vector<double>& x1, const std::vector<double>& x2) const;
	int majorityElement(const std::vector<int>& elements) const;

public:
	KNN();
	KNN(int k);
	~KNN();
	void fit(const std::vector<std::vector<double>>& X_train, const std::vector<int>& y_train) override; //nadaje wartosci
	int predict(std::vector<double> point) const override;
	std::vector<int> predict(std::vector<std::vector<double>> points) const override;
};
