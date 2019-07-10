//
//  neuralclass.h
//  neuralnet
//
//  Created by Fabricio Bracht on 2019-06-30.
//  Copyright © 2019 Fabricio Bracht. All rights reserved.
//

#ifndef neuralclass_h
#define neuralclass_h

struct Neural {
    size_t inodes;
    size_t hnodes;
    size_t onodes;
    double learningrate;
    
    Neural() {
        inodes = 3;
        hnodes = 3;
        onodes = 3;
        learningrate = 0.3;
    }
    
    void activation(Matrix<double>& ref, Matrix<double>& dest) {
        int i, j;
        for (i = 0; i < ref.rows(); ++i) {
            for (j = 0; j < ref.cols(); ++j) {
                dest[i][j] = 1/(1+exp(-(ref[i][j]))); }
        }
    }
    
    void train() {
        
    }
    
    Matrix<double> query(Matrix<double>& inputs, Matrix<double>& wih, Matrix<double>& who) {
        Matrix<double> hidden_inputs(wih.cols(), inputs.rows());
        Matrix<double> hidden_outputs(wih.cols(), inputs.rows());
        Matrix<double> final_inputs(wih.cols(), inputs.rows());
        Matrix<double> final_outputs(wih.cols(), inputs.rows());
        
        // Calculates signals into the hidden layer
        hidden_inputs = wih * inputs;
        
        // Calculate signals emerging from hidden layer
        activation(hidden_inputs, hidden_outputs);
        
        // Calculate signals into final output layer
        final_inputs = who * hidden_outputs;
        
        // Calculate signals emerging from final output layer
        activation(final_inputs, final_outputs);
        
        return final_outputs;
        
    }
};

#endif /* neuralclass_h */
