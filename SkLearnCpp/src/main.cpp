#include <iostream>
#include "../include/data/DataLoader.h"
#include "../include/preprocessing/preprocessor.h"
#include "../include/preprocessing/LabelEncoder.h"
#include "../include/data/Utilities.h"
#include "../include/algorithms/knn.h"
#include "../include/algorithms/DecisionTree.h"
#include "../include/visualization/PlottingUtils.h"

double accuracy(std::vector<int> y_pred, std::vector<int> y) {
    double sum = 0;
    for (int i = 0; i < y_pred.size(); i++) {
        if (y_pred[i] == y[i]) {
            sum += 1;
        }
    }
    return sum / y_pred.size();
}

int main() {
    //Wczytanie danych
    DataLoader<double> orginalData;
    orginalData.loadFromFile("C:/Users/ola86/Desktop/iris.csv");


    //Ograniczenie si� do 2 kolumn w celu u�atwienia rysowania
    std::vector<std::vector<double>> X = extractTwoColumns(orginalData.data, 2, 3);
    //std::vector<std::vector<double>> X = orginalData.data;
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
    //MinMaxScaler scaler;
    StandardScaler scaler;
    scaler.fit(X_train);
    auto X_train_std = scaler.transform(X_train);
    auto X_test_std = scaler.transform(X_test);

    //Wyb�r klasyfikatora
    KNN clf(7);
    /*DecisionTree clf;*/
    clf.fit(X_train_std, y_train);
    auto y_test_pred = clf.predict(X_test_std);
    auto y_train_pred = clf.predict(X_train_std);

    //Wyniki
    //Trafnosc predykcji dla zbioru treningowe i testowego!!
    std::cout << "Dokladnosc na zbiorze treningowym: " << accuracy(y_train_pred, y_train) << std::endl;
    std::cout << "Dokladnosc na zbiorze testowym: " << accuracy(y_test_pred, y_test) << std::endl;

    //Stworzenie skryptu dla gnuplota do wyrysowania wynik�w
    plotDecisionRegions(X_train_std, y_train, X_test_std, y_test, clf);

    return 0;
}
