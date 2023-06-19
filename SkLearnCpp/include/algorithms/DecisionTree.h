#ifndef DECISIONTREE_H
#define DECISIONTREE_H

//#pragma once
#include "Classifier.h"
#include "../data/DataLoader.h"
#include "../data/Node.h"
#include "../data/Utilities.h"
#include <iostream>
#include <string>
#include <math.h>

class DecisionTree: public Classifier{
    std::vector< std::vector<double> >entries;
    std::vector<int> labels_dict;
    int max_depth=4;
    const int minDepth=5;
    Node<double>* root;

    int num_of_features;
    int num_of_rows;
    int num_of_labels;

    int mostOccuredLabel(std::vector< std::vector<double>* >& v);
    double calcEntropy(std::vector< std::vector<double>* > &v);
    void fitNode(Node<double>* node, std::vector< std::vector<double>* > &v, int depth_level);
    double calcInformationGain(Condition<double> c, std::vector< std::vector<double>* > &v, double parent_information_content);
    
    //int mostOccuredLabel(std::vector< std::vector<double>* > &v);
    int predictNode(const std::vector<double> &v, Node<double>* node, int depth_level);
   
    public:
    DecisionTree(): root(new Node<double>){}
    ~DecisionTree() = default;

    //bool loadData(std::string filename);
    //void setDepth(int d);
    void fit(const std::vector<std::vector<double>>& X_train, const std::vector<int>& y_train);
    int predict(std::vector<double> point);
    std::vector<int> predict(std::vector<std::vector<double>> v);
    
    void printNode(Node<double>* node);
    void displayNodes();
};

#endif