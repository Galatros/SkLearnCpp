#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>
#include <random>
#include <algorithm>


//declarations
std::string parse_extension(std::string filename);
std::vector<std::vector<double>> extractTwoColumns(const std::vector<std::vector<double>>& matrix, int xColumnIndex, int yColumnIndex);
template<typename T> double log_base(T var);
template<typename T> T* find_min(std::vector<T> v);
template<typename T> T* find_max(std::vector<T> v);
template<typename T> int find(const std::vector<T>& v, T key);
template<typename T> void display_vector_contents(std::vector<T> v);
template<typename T> void display_vector_contents(std::vector< std::vector<T> > v);
template <typename T> void train_test_split(const std::vector<T>& data, std::vector<T>& train_data, std::vector<T>& test_data, float test_size, unsigned int random_state = 0);
template <typename T> void train_test_split(const std::vector<std::vector<T>>& data, std::vector<std::vector<T>>& train_data, std::vector<std::vector<T>>& test_data, float test_size, unsigned int random_state = 0);
template <typename T> void train_test_split(const std::vector<std::vector<T>>& data, std::vector<int>& labels, std::vector<std::vector<T>>& X_train, std::vector<int>& y_train, std::vector<std::vector<T>>& X_test, std::vector<int>& y_test, double test_size, unsigned int random_state = 0);



//template definitions

template <typename T>double log_base(double base, T var) {
    double v = (double)var;
    if (base <= 0) {
        std::cout << "Error. Log base <= 0." << std::endl;
        exit(1);
    }
    if (var == 0) return 0;
    return (log(v) / log(base));
}
template<typename T> T* find_min(std::vector<T> v) {
    T* smallest = v.begin();
    for (int i = 1; i < v.size(); i++) {
        if (v[i] < *smallest) smallest = &v[i];
    }
    return smallest;
}
template<typename T> T* find_max(std::vector<T> v) {
    T* greatest = v.begin();
    for (int i = 1; i < v.size(); i++) {
        if (v[i] > *greatest) greatest = &v[i];
    }
    return greatest;
}
template<typename T> int find(const std::vector<T>& v, T key) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == key) return i;
    }
    return -1;
}
template<typename T> void display_vector_contents(std::vector<T> v) {
    int space = 10;
    std::cout << "Vector contents: " << std::endl;
    std::cout << std::setw(space) << "Index   Value" << std::endl;
    for (int i = 0; i < v.size(); i++) {
        std::cout << i << " " << v[i] << std::endl;
    }
    return;
}
template<typename T> void display_vector_contents(std::vector< std::vector<T> > v) {
    int space = 10;
    std::cout << std::setw(space) << "Vector contents: " << std::endl;
    std::cout << std::setw(space) << "Index" << std::setw(space) << "Contents" << std::endl;
    for (int i = 0; i < v.size(); i++) {
        std::cout << std::setw(space) << i;
        for (int j = 0; j < v[i].size(); j++) {
            std::cout << std::setw(space) << v[i][j];
        }
        std::cout << std::endl;
    }
    return;
}
template<typename T> void display_vector_contents(std::vector< std::vector<T>* > v) {
    int space = 10;
    std::cout << std::setw(space) << "Vector contents: " << std::endl;
    std::cout << std::setw(space) << "Index" << std::setw(space) << "Contents" << std::endl;
    for (int i = 0; i < v.size(); i++) {
        std::cout << std::setw(space) << i;
        for (int j = 0; j < v[i]->size(); j++) {
            std::cout << std::setw(space) << v[i]->at(j);
        }
        std::cout << std::endl;
    }
    return;
}

template <typename T> void train_test_split(const std::vector<T>& data, std::vector<T>& train_data, std::vector<T>& test_data, float test_size, unsigned int random_state) {
    if (test_size <= 0.0 || test_size >= 1.0) {
        std::cerr << "B³¹d: test_size musi byæ wartoœci¹ z przedzia³u (0, 1)" << std::endl;
        return;
    }

    std::mt19937 rng(random_state);
    std::vector<size_t> indices(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        indices[i] = i;
    }
    std::shuffle(indices.begin(), indices.end(), rng);

    size_t split_index = static_cast<size_t>(data.size() * (1.0 - test_size));

    train_data.clear();
    train_data.reserve(split_index);
    for (size_t i = 0; i < split_index; ++i) {
        train_data.push_back(data[indices[i]]);
    }

    test_data.clear();
    test_data.reserve(data.size() - split_index);
    for (size_t i = split_index; i < data.size(); ++i) {
        test_data.push_back(data[indices[i]]);
    }
}


template <typename T> void train_test_split(const std::vector<std::vector<T>>& data, std::vector<std::vector<T>>& train_data, std::vector<std::vector<T>>& test_data, float test_size, unsigned int random_state) {
    if (test_size <= 0.0 || test_size >= 1.0) {
        std::cerr << "B³¹d: test_size musi byæ wartoœci¹ z przedzia³u (0, 1)" << std::endl;
        return;
    }

    std::mt19937 rng(random_state);
    std::vector<size_t> indices(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        indices[i] = i;
    }
    std::shuffle(indices.begin(), indices.end(), rng);

    size_t split_index = static_cast<size_t>(data.size() * (1.0 - test_size));

    train_data.clear();
    train_data.reserve(split_index);
    for (size_t i = 0; i < split_index; ++i) {
        train_data.push_back(data[indices[i]]);
    }

    test_data.clear();
    test_data.reserve(data.size() - split_index);
    for (size_t i = split_index; i < data.size(); ++i) {
        test_data.push_back(data[indices[i]]);
    }
}

template <typename T> void train_test_split(const std::vector<std::vector<T>>& data, std::vector<int> &labels, std::vector<std::vector<T>>& X_train, std::vector<int>& y_train, std::vector<std::vector<T>>& X_test, std::vector<int>& y_test, double test_size, unsigned int random_state) {
    if (test_size <= 0.0 || test_size >= 1.0) {
        std::cerr << "B³¹d: test_size musi byæ wartoœci¹ z przedzia³u (0, 1)" << std::endl; //TODO Wykorzystano std::cerr w obawie przed zaburzeniem wypisywania danych, ale mo¿e lepiej throw lub cout?
        return;
    }

    std::mt19937 rng(random_state);
    std::vector<size_t> indices(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        indices[i] = i;
    }
    std::shuffle(indices.begin(), indices.end(), rng);

    size_t split_index = static_cast<size_t>(data.size() * (1.0 - test_size));

    X_train.clear();
    X_train.reserve(split_index);
    y_train.clear();
    y_train.reserve(split_index);
    for (size_t i = 0; i < split_index; ++i) {
        X_train.push_back(data[indices[i]]);
        y_train.push_back(labels[indices[i]]);
    }

    X_test.clear();
    X_test.reserve(data.size() - split_index);
    y_test.clear();
    y_test.reserve(data.size() - split_index);
    for (size_t i = split_index; i < data.size(); ++i) {
        X_test.push_back(data[indices[i]]);
        y_test.push_back(labels[indices[i]]);
    }
}

#endif