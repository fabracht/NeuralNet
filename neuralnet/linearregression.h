//
//  linearregression.h
//  neuralnet
//
//  Created by Fabricio Bracht on 2019-07-01.
//  Copyright © 2019 Fabricio Bracht. All rights reserved.
//

#ifndef linearregression_h
#define linearregression_h
#include <cstdio>
#include <cstdlib>
#include <tuple>
#include <numeric>
#include <cmath>
#include <limits>
#include "dynarray.h"

using namespace std;

class linearRegression {
public:
    // Default Constructor
    linearRegression();
    // Default Destructor
//    ~linearRegression();
    // Non-default Constructor
    linearRegression(dynArray<double> & _m_x_vals, dynArray<double> & _m_y_vals) :
    m_x_vals(_m_x_vals), m_y_vals(_m_y_vals), m_num_elements(_m_y_vals.size()), m_old_error(numeric_limits<double>::max()) {}
    // While loop that perfors the adjusting of coef a and b
    void trainAlgorithm(int, double, double);
    // Calculates the result of a*x + b and returns it
    double regress(double);

private:
    dynArray<double> m_x_vals;
    dynArray<double> m_y_vals;
    double m_num_elements;
    double m_old_error;
    double m_a;
    double m_b;
    
    bool isConverged();
};

void linearRegression::trainAlgorithm(int num_iter, double a_init, double b_init) {
    int iter = 0;
    //double m_a_old, m_b_old;
    m_a = a_init;
    m_b = b_init;
    double step, a_grad, b_grad;
    
    // Set the initial gradient
    a_grad = 0.;
    b_grad = 0.;
    while (!isConverged() && iter < num_iter) {
        printf("--------- Iteration %d -----------\n", iter);
        step = 2. / static_cast<double>(iter + 2);
        // compute the gradient of the error wrt a
        for (int i = 0; i < m_num_elements; ++i) {
            a_grad += m_x_vals[i] * (( m_a  * m_x_vals[i] + m_b) - m_y_vals[i]);
        }
        a_grad = (2 * a_grad) / m_num_elements;
        
        // computer the gradient of the error wrt b
        for (int i = 0; i < m_num_elements; ++i) {
            b_grad += (( m_a  * m_x_vals[i] + m_b) - m_y_vals[i]);
        }
        b_grad = (2 * b_grad) / m_num_elements;
        
        // Take the step
        m_a -= (step * a_grad);
        m_b -= (step * b_grad);
        // Update the step size

        printf("a: %lf,\tb: %lf\r\n", m_a, m_b);
        printf("a_grad: %lf,\tb_grad:%lf\r\n", a_grad, b_grad);
        iter++;
    }
}

// Implement the Regress function
double linearRegression::regress(double x) {
    double res = m_a * x + m_b;
    return res;
}

// Check for convergence
bool linearRegression::isConverged() {
    double error = 0.;
    double threshold = 0.001;
    for (int i = 0; i < m_num_elements; ++i) {
        error += ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]) * ((m_a * m_x_vals[i] + m_b) - m_y_vals[i]);
    }
    error /= m_num_elements;
    printf("Error = %lf\n", error);
    bool criteria = abs(error - m_old_error) < threshold;
    m_old_error = error;
    return criteria;
}

void LinFit(double x[], double y[], double sigmy[], int n, int iopt,
            double &a, double &b, double &sigma, double &sigmb, double &chi2) {
//---------------------------------------------------------------------------
// Determines the coefficients a and b of a linear model P(x;a,b) = a * x + b
// and the associated uncertainties, sigma and sigmb, for a set of observed
// data points by "Chi-square" regression
// x[] - x-coordinates of observed data, i = 1,..,n
// y[] - y-coordinates of observed data
// sigmy[] - standard deviations of observed data
// n - number of observed data points
// iopt - iopt == 0 - initializes sigmy[i] = 1 (equal weights)
// - iopt != 0 - uses the received values of sigmy[i]
// a, b - parameters of the linear model (output)
// sigma - uncertainties associated with the model parameters (output)
// sigmb
// chi2 - value of Chi-square merit function for the output parameters
//---------------------------------------------------------------------------
    double f, s, sx, sy, sxx, sxy;
    int i;
    if (iopt == 0)
        for (i=1; i<=n; i++) sigmy[i] = 1e0; // iopt = 0: equall weights
    s = sx = sy = sxx = sxy = 0e0; // prepare sums
    for (i=1; i<=n; i++) {
        f = 1e0/(sigmy[i]*sigmy[i]);
        s += f;
        sx += x[i] * f; sxx += x[i] * x[i] * f;
        sy += y[i] * f; sxy += x[i] * y[i] * f;
    }
    f = 1e0/(s*sxx - sx*sx);
    a = (s *sxy - sx*sy ) * f; sigma = sqrt(s*f); // model parameters
    b = (sy*sxx - sx*sxy) * f; sigmb = sqrt(sxx*f); // and uncertainties
    chi2 = 0e0; // value of Chi-square function
    for (i=1; i<=n; i++) {
        f = (y[i] - a*x[i] - b)/sigmy[i];
        chi2 += f*f;
    }
}

#endif /* linearregression_h */
