#pragma once
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

class KNN
{
private:
	std::vector<std::vector<double>> X_train; //macierz danych treningowych
	std::vector<int> y_train; //etykiety danych treningowych
	int k; //liczba najblizszych sasiadow

	double euclideanDistance(const std::vector<double>& x1, const std::vector<double>& x2);
	int majorityElement(const std::vector<int>& elements);

public:
	void fit(const std::vector<std::vector<double>>& X_train, const std::vector<int>& y_train, int k); //nadaje wartosci
	int predict(std::vector<double> point);
};
