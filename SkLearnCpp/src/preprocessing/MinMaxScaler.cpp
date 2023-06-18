#include "../../include/preprocessing/preprocessor.h"

MinMaxScaler::MinMaxScaler() : featureRange(0.0, 1.0) {}

MinMaxScaler::~MinMaxScaler() {}

void MinMaxScaler::fit(const std::vector<std::vector<double>>& data) 
{
    if (data.empty()) {
        return;
    }

    //Number of columns
    const size_t numFeatures = data[0].size();

    //Prepare the appropriate size of vectors 
    dataMin.resize(numFeatures, std::numeric_limits<double>::max());
    dataMax.resize(numFeatures, std::numeric_limits<double>::lowest());

    //Creation of vectors for minimum and maximum values for each column
    for (const auto& sample : data) {
        for (size_t i = 0; i < numFeatures; ++i) {
            dataMin[i] = std::min(dataMin[i], sample[i]);
            dataMax[i] = std::max(dataMax[i], sample[i]);
        }
    }

}

std::vector<std::vector<double>> MinMaxScaler::transform(const std::vector<std::vector<double>>& data) const 
{
    std::vector<std::vector<double>> scaledData(data.size(), std::vector<double>(data[0].size()));

    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            double value = data[i][j];
            double dataMinValue = dataMin[j];
            double dataMaxValue = dataMax[j];

            double scaledValue = (value - dataMinValue) /
                (dataMaxValue - dataMinValue) *
                (featureRange.second - featureRange.first) + featureRange.first;

            scaledData[i][j] = scaledValue;
        }
    }

    return scaledData;
}

std::vector<std::vector<double>> MinMaxScaler::fit_transform(const std::vector<std::vector<double>>& data) {
    fit(data);
    return transform(data);
}

std::vector<std::vector<double>> MinMaxScaler::inverse_transform(const std::vector<std::vector<double>>& scaled_data) const {
    std::vector<std::vector<double>> data(scaled_data.size(), std::vector<double>(scaled_data[0].size()));

    for (size_t i = 0; i < scaled_data.size(); ++i) {
        for (size_t j = 0; j < scaled_data[i].size(); ++j) {
            double scaledValue = scaled_data[i][j];
            double dataMinValue = dataMin[j];
            double dataMaxValue = dataMax[j];

            double originalValue = (scaledValue - featureRange.first) /
                (featureRange.second - featureRange.first) *
                (dataMaxValue - dataMinValue) + dataMinValue;

            data[i][j] = originalValue;
        }
    }

    return data;
}