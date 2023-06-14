#include"../../include/algorithms/knn.h"

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
		if (element == suspect) count += 1;
		else count -= 1;
	}

	return suspect;
}

int KNN::predict(std::vector<double> point)
{
	std::vector<double>distances; //vector przechowujacy odleglosci point od punktow treningowych;
	std::vector<int>nearestNeighbors; //vector przechowujacy sasiadow;

	// 1) obliczenie odleglosci euklidesowych miedzy pkt a pkt zbioru treningowego (petla for) i wsadzanie ich do distances
	for (int i = 0; i < X_train.size(); i++)
	{
		double distance = euclideanDistance(point, X_train[i]);
		distances.push_back(distance);
	}

	// 2) sortowanie odleglosci
	std::sort(distances.begin(), distances.end(), std::greater<>());

	// 3) wybor k najblizszych sasiadow
	for (int i = 0; i < k; i++)
	{
		nearestNeighbors.push_back(distances[i]);
	}

	// 4) glosowanie wiekszosciowe za poprawna etykieta (typ danych unoredered_map)
	int predicted{};
	predicted = majorityElement(nearestNeighbors);

	return predicted;

}

