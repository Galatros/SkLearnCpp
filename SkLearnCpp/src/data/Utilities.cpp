#include "../../include/data/Utilities.h"

std::vector<std::vector<double>> extractTwoColumns(const std::vector<std::vector<double>>& matrix, int xColumnIndex, int yColumnIndex) {
    std::vector<std::vector<double>> extractedColumns;

    for (const auto& row : matrix) {
        std::vector<double> extractedRow;
        extractedRow.push_back(row[xColumnIndex]);
        extractedRow.push_back(row[yColumnIndex]);
        extractedColumns.push_back(extractedRow);
    }

    return extractedColumns;
}

std::string parse_extension(std::string filename) {
    size_t pos = filename.find(".txt");
    if (pos == filename.size() - 4)
        return ".txt";

    pos = filename.find(".csv");
    if (pos == filename.size() - 4)
        return ".csv";


    throw (std::string)("Unknown file extension. Supported extensions are .txt and .csv");
}

