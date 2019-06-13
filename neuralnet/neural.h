//
//  neuralclass.h
//  neuralnetwork1
//
//  Created by Fabricio Bracht on 2019-06-10.
//  Copyright © 2019 Fabricio Bracht. All rights reserved.
//

#ifndef neural_h
#define neural_h
#include <iostream>
#include <cmath>
#include <random>
#include "linkedl.h"

using namespace std;

// Generate a random number between -1 and 1
double generateRandomNum() {
    random_device r;
    default_random_engine el(r());
    uniform_real_distribution<double> uniform_dist(-1.0, 1.0);
    double num = uniform_dist(el);

    return num;
}

template<typename T>
class neuralNetwork : public linkedl<T>{
private:
    int inputnodes, hiddennodes, outputnodes; // size of the network
    T learningrate; // self-explanatory
    linkedl<T> **coefMatrix; // coeficient matrix
public:
    // Initialize the neural network
    neuralNetwork();
    neuralNetwork(int _inputnodes, int _hiddennodes, int _outputnodes, T _learningrate);
    neuralNetwork(const neuralNetwork&); // copy constructor
    ~neuralNetwork(); // default destructor
    // Train the neural network
    void train() {};
    // Query the neural network
    void query() {};
};

template<typename T>
neuralNetwork<T>::neuralNetwork() {
    inputnodes = hiddennodes = outputnodes = 3;
    learningrate = 0.3;
    coefMatrix = new linkedl<T>*[3];
    for (int i = 0; i < 3; ++i) {
        coefMatrix[i%3] = new linkedl<T>;
    }
    for(int i = 0; i < 9; ++i) {
        coefMatrix[i%3]->add(generateRandomNum());
    }
}

template<typename T>
neuralNetwork<T>::neuralNetwork(int _inputnodes, int _hiddennodes, int _outputnodes, T _learningrate) {
    inputnodes(_inputnodes);
    hiddennodes(_hiddennodes);
    outputnodes(_outputnodes);
    int dimension = max(inputnodes, max(hiddennodes, outputnodes));
    coefMatrix = new linkedl<T>*[dimension];
}

template<typename T>
neuralNetwork<T>::~neuralNetwork() {
    delete[] coefMatrix;
    cout << "Neural destroyed" << endl;
}

#endif /* neuralclass_h */
