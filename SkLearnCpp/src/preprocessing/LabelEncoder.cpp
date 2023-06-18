#include "../../include/preprocessing/LabelEncoder.h"

void LabelEncoder::fit(const std::vector<std::string>& labels) 
{
    indexMap.clear();
    int index = 0;
    for (const auto& label : labels) 
    {
        if (indexMap.find(label) == indexMap.end()) 
        {
            indexMap[label] = index;
            index++;
        }
    }
}

std::vector<int> LabelEncoder::transform(const std::vector<std::string>& labels) const 
{
    std::vector<int> encodedLabels;
    for (const auto& label : labels) 
    {
        if (indexMap.find(label) != indexMap.end()) 
        {
            encodedLabels.push_back(indexMap.at(label)); //U¿yto at by zapewniæ, ¿e mapa nie zostanie zmodyfikowana
        }
        else 
        {
            throw (std::string)("Label transform failed. Unknow label. Consider using fit again.");
            //encodedLabels.push_back(-1);
        }
    }
    return encodedLabels;
}

std::vector<std::string> LabelEncoder::inverse_transform(const std::vector<int>& encodedLabels) const 
{
    std::vector<std::string> labels;
    for (const auto& encodedLabel : encodedLabels) {
        bool found = false;
        for (const auto& pair : indexMap) 
        {
            if (pair.second == encodedLabel) 
            {
                labels.push_back(pair.first);
                found = true;
                break;
            }
        }
        if (!found) 
        {
            throw (std::string)("Label transform failed. Unknow label. Consider using fit again.");
            //labels.push_back("");
        }
    }
    return labels;
}

std::vector<int> LabelEncoder::fit_transform(const std::vector<std::string>& labels) 
{
    fit(labels);
    return transform(labels);
}