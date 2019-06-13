//
//  main.cpp
//  neuralnet
//
//  Created by Fabricio Bracht on 2019-06-11.
//  Copyright © 2019 Fabricio Bracht. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "neural.h"
#include "linkedl.h"

using namespace std;

int main(int argc, const char * argv[]) {
    double A[] = {1.1, 2.2, 3.3};
    linkedl<double> ll(A, 3);
    ll.print();
    double second = ll.getnthvalue(1);
    cout << "The second value is " << second << endl;
    
    neuralNetwork<double> nn;

    
    return 0;
}
