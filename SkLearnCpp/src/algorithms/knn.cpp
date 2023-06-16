#include"../../include/algorithms/knn.h"


void KNN::fit(const std::vector<std::vector<double>>& X_train, const std::vector<int>& y_train, int k) //nadaje wartosci
{
	this->X_train = X_train;
	this->y_train = y_train;
	this->k = k;
}

double KNN::euclideanDistance(const std::vector<double>& x1, const std::vector<double>& x2)
{
	double d{};
	for (int i = 0; i < x1.size(); i++)
	{
		d += std::pow(x1[i] - x2[i], 2);
	}
	d = std::sqrt(d);
	return d;
}

int KNN::majorityElement(const std::vector<int>& elements)
{
	//Moore's Voting Algorithm

	int count{};
	int suspect{}; //element podejrzany o bycie wiekszoscia

	for (int element : elements)
	{
		if (count == 0)
		{
			suspect = element;
		}
		if (element == suspect) 
		{ 
			count += 1; 
		}
		else
		{
			count -= 1;
		}
	}

	return suspect;
}

int KNN::predict(std::vector<double> point)
{
	std::vector<std::pair<double, int>> distances; // wektor przechowuj�cy pary (odleg�o��, etykieta)
	std::vector<int> nearestNeighbors; // wektor przechowuj�cy s�siad�w

	// 1) obliczenie odleg�o�ci euklidesowych mi�dzy pkt a pkt z zbioru treningowego
	for (int i = 0; i < X_train.size(); i++)
	{
		double distance = euclideanDistance(point, X_train[i]);
		distances.push_back(std::make_pair(distance, y_train[i]));
	}

	// 2) sortowanie odleg�o�ci
	std::sort(distances.begin(), distances.end());

	// 3) wyb�r k najbli�szych s�siad�w
	for (int i = 0; i < k; i++)
	{
		nearestNeighbors.push_back(distances[i].second);
	}

	// 4) g�osowanie wi�kszo�ciowe za poprawn� etykiet�
	int predicted = majorityElement(nearestNeighbors);

	return predicted;
}

