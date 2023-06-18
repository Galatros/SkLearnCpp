#include "../../include/preprocessing/preprocessor.h"
#include <numeric>
#include <cmath>

StandardScaler::~StandardScaler() {}

void StandardScaler::fit(const std::vector<std::vector<double>>& data)
{
    if (data.empty()) {
        return;
    }

    //Number of columns
    const size_t numFeatures = data[0].size();

    //Prepare the appropriate size of vectors 
    means.resize(numFeatures);
    stds.resize(numFeatures);

    //Creation of vectors for means and standard deviation for each column
    for (size_t i = 0; i < numFeatures; ++i) {
        double sum = 0.0;
        for (const auto& row : data) {
            sum += row[i];
        }
        means[i] = sum / data.size();

        //means[i] = std::accumulate(data[i].begin(), data[i].end(), 0.0)/data.size();

        double squaredSum = 0.0;
        for (const auto& row : data) {
            squaredSum += std::pow(row[i] - means[i], 2);
        }
        stds[i] = std::sqrt(squaredSum / data.size());
    }
}

std::vector<std::vector<double>> StandardScaler::transform(const std::vector<std::vector<double>>& data) const
{
    std::vector<std::vector<double>> scaledData(data.size(), std::vector<double>(data[0].size()));

    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            double value = data[i][j];
            double mean = means[j];
            double std = stds[j];

            double scaledValue = (value - mean) / std;

            scaledData[i][j] = scaledValue;
        }
    }

    return scaledData;
}

std::vector<std::vector<double>> StandardScaler::fit_transform(const std::vector<std::vector<double>>& data) {
    fit(data);
    return transform(data);
}

std::vector<std::vector<double>> StandardScaler::inverse_transform(const std::vector<std::vector<double>>& scaled_data) const {
    std::vector<std::vector<double>> data(scaled_data.size(), std::vector<double>(scaled_data[0].size()));

    for (size_t i = 0; i < scaled_data.size(); ++i) {
        for (size_t j = 0; j < scaled_data[i].size(); ++j) {
            double scaledValue = scaled_data[i][j];
            double mean = means[j];
            double std = stds[j];

            double originalValue = (scaledValue * std) + mean;

            data[i][j] = originalValue;
        }
    }

    return data;
}