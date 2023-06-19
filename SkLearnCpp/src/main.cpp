#include <iostream>
#include "../include/data/DataLoader.h"
#include "../include/preprocessing/preprocessor.h"
#include "../include/preprocessing/LabelEncoder.h"
#include "../include/data/Utilities.h"
//#include "../include/algorithms/knn.h"
#include "../include/algorithms/DecisionTree.h"
#include "../include/visualization/PlottingUtils.h"

int main() {
    //Wczytanie danych
    DataLoader<double> orginalData;
    orginalData.loadFromFile("C:\\Users\\tobia\\Downloads\\iris.csv");


    //Ograniczenie si� do 2 kolumn w celu u�atwienia rysowania
    //std::vector<std::vector<double>> X = extractTwoColumns(orginalData.data, 2, 3);
    std::vector<std::vector<double>> X = orginalData.data;
    //Konwersja Labels na Inty
    LabelEncoder labelEncoder;
    std::vector<int> y = labelEncoder.fit_transform(orginalData.labels);

    //Podzielenie zbioru na zbi�r danych treningowych i testowych
    std::vector<std::vector<double>> X_train;
    std::vector<int> y_train;
    std::vector<std::vector<double>> X_test;
    std::vector<int> y_test;
    train_test_split(X, y, X_train, y_train, X_test, y_test, 0.19, 42);

    //Standaryzacja danych
    MinMaxScaler scaler;
    scaler.fit(X_train);
    auto X_train_std = scaler.transform(X_train);
    auto X_test_std = scaler.transform(X_test);

    //Wyb�r klasyfikatora
    //KNN knn(7);
    //knn.fit(X_train_std, y_train);
    DecisionTree clf;
    clf.fit(X_train_std, y_train);
    clf.predict(X_test_std);

    //Wyniki
    //TODO trafno�c predykcji dla zbioru treningowe i testowego!!

    //Stworzenie skryptu dla gnuplota do wyrysowania wynik�w
    //plotDecisionRegions(X_train_std, y_train, X_test_std, y_test, clf);

    return 0;
}
