//
//  main.cpp
//  neuralnet
//
//  Created by Fabricio Bracht on 2019-06-11.
//  Copyright © 2019 Fabricio Bracht. All rights reserved.
//

//#include <ctime>
//#include <cmath>
//#include "linkedl.h"
//#include "neural.h"
//#include "dynarray.h"
//#include "neuraldyn.h"
//#include "linearregression.h"
#include "myvector.h"
//#include <Eigen/Dense>
#include <iostream>
#include "matrix.h"
#include "neural.h"


using namespace std;
//using namespace Eigen;



int main(int argc, const char * argv[]) {
    Neural n;
    Matrix<double> wih(n.inodes, n.hnodes);
    Matrix<double> who(n.hnodes, n.onodes);
    wih.rand(-0.5, 0.5);
    who.rand(-0.5, 0.5);

    Matrix<double> inputs(n.hnodes);
    inputs.rand(0.1, 0.3);
    
    Matrix<double> hidden_inputs(wih.rows(), inputs.cols());
    Matrix<double> final_outputs(wih.rows(), inputs.cols());
    final_outputs = n.query(inputs, wih, who);
    final_outputs.print();
    
    return 0;
}
