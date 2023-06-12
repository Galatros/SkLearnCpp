#include <iostream>
#include "../include/DataLoader.h"
#include "../include/Utilities.h"

int main(){ 
    DataLoader<std::string> data1;
    data1.load_data("file2.csv");
    data1.display_data();

    DataLoader<float> data2;
    data2.load_data("file1.txt");
    data2.display_data();

    DataLoader<long> data3;
    data3.load_data("file2.csv");
    data3.display_data();

    DataLoader<int> data4;
    data4.load_data("file2.csv");
    data4.display_data();

    DataLoader<long long> data5;
    data5.load_data("file2.csv");
    data5.display_data();
    return 0;
}