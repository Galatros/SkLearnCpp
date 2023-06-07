#pragma once
#include<vector>
#include<cmath>
using namespace std;

class KNN
{
private:
	std::vector<std::vector<double>> X_train; //macierz danych treningowych
	std::vector<int> y_train; //etykiety danych treningowych
	int k; //liczba najblizszych sasiadow

public:
	void fit(const std::vector<std::vector<double>>& X_train, const std::vector<int>& y_train, int k) //nadaje wartosci
	{
		this->X_train = X_train;
		this->y_train = y_train;
		this->k = k;
	}
	int predict(std::vector<double> point)
	{
		// 1) obliczenie odleglosci euklidesowych miedzy pkt a pkt zbioru treningowego (petla for)
		// 2) sortowanie odleglosci
		// 3) wybor k najblizszych sasiadow
		// 4) glosowanie wiekszosciowe za poprawna etykieta (typ danych unoredered_map)
	}

};
