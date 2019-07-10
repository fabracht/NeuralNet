//
//  mymatrix.hpp
//  neuralnet
//
//  Created by Fabricio Bracht on 2019-07-08.
//  Copyright © 2019 Fabricio Bracht. All rights reserved.
//

#ifndef matrix_h
#define matrix_h

//#include <iostream>
#include <random>

template<typename T>
class Matrix {
public:
    Matrix(); // Default constr, 8x8 empty matrix
    ~Matrix(); // Default destructor
    Matrix(const Matrix &other); // Copy
    Matrix(size_t); // Custom Constructor
    Matrix(size_t, size_t); // Custom Constructor
    void zero(); // Fills the matrix with zeros
    void value(T);
    void rand(double, double); // Fills the matrix with random double numbers
    void print(); // Prints the matrix
    size_t rows() { return ni; }; // Returns the number of rows
    size_t cols() { return nj; }; // Returns the number of collumns
    
    // Returns a row in the matrix, nullptr if out of bounds
    T* operator [](size_t) const;
    Matrix<T>& operator=(const Matrix&);
    bool operator==(const Matrix&);
    
    // Matrix Scalar Operations
    Matrix<T> operator*(T);
    Matrix<T> operator+(T);
    Matrix<T> operator-(T);
    Matrix<T> operator/(T);
    Matrix<T>& operator*=(T);
    Matrix<T>& operator+=(T);
    Matrix<T>& operator-=(T);
    Matrix<T>& operator/=(T);
    
    // Matrix operations
    Matrix<T> trans(); // Returns the transpose of the matrix
    Matrix<T> operator+(const Matrix<T>& rhs);
    Matrix<T> operator-(const Matrix<T>& rhs);
    Matrix<T> operator*(const Matrix<T>& rhs);
    
    Matrix<T>& operator+=(const Matrix<T>& rhs);
    Matrix<T>& operator-=(const Matrix<T>& rhs);
    Matrix<T>& operator*=(const Matrix<T>& rhs);
    
    void map(T (*func_callback)(T));
    
private:
    T** matrix; // pointer to Matrix origin
    size_t ni; // number of rows
    size_t nj; // number of cols
    
    void swap(T * a, T * b);
    double generateRandomNum(double start, double end);
};


//===========================================================================
//---------------------------------------------------------------------------
// Allocates a T 8x8 matrix allocated with Matrix
//---------------------------------------------------------------------------
template<typename T>
Matrix<T>::Matrix() {
    int i;
    ni = 8, nj = 8; // numbers of rows and columns
    // allocate array of row pointers
    //    matrix = (T**) malloc((size_t)(ni*sizeof(T*)));
    matrix = new T*[ni];
    if (!matrix) {
        printf("Matrix: level 1 allocation error !\n");
        exit(1);
    }
    
    // assign block start to 1st row pointer
    // define row pointers spaced by row length
    for (i = 0; i < ni; i++) {
        matrix[i] = new T[nj];
        //        matrix[i] = (T*) malloc((size_t)(nj*sizeof(T)));
        //        matrix[i] = matrix[i-1] + nj;
    }
    if (!matrix[0]) {
        printf("Matrix: level 2 allocation error !\n");
        exit(2);
    }
}

//===========================================================================
//---------------------------------------------------------------------------
// Default Destructor
//---------------------------------------------------------------------------
template<typename T>
Matrix<T>::~Matrix() {
    for (int i = 0; i < ni; ++i) {
        delete[] matrix[i];
        //        matrix[i] = nullptr;
        //        free((void*) (matrix[i])); // deallocate block
    }
    delete[] matrix;
    //    free((void*) (matrix)); // deallocate array of row pointers
}

template<typename T>
Matrix<T>::Matrix(const Matrix &other) { // Copy
    ni = other.ni;
    nj = other.nj;
    int i, j;
    // allocate array of row pointers
    //    matrix = (T**) malloc((size_t)(ni*sizeof(T*)));
    matrix = new T*[ni];
    if (!matrix) {
        printf("Matrix: level 1 allocation error !\n");
        exit(1);
    }
    
    // assign block start to 1st row pointer
    for (i = 0; i < ni; i++) {
        matrix[i] = new T[nj];
        //        matrix[0] = (T*) malloc((size_t)(ni*nj*sizeof(T)));
        //        matrix[i] = matrix[i-1] + nj;
    }
    if (!matrix[0]) {
        printf("Matrix: level 2 allocation error !\n");
        exit(2);
    }
    // define row pointers spaced by row length
    for (i = 0; i < ni; ++i) {
        for (j = 0; j < nj; ++j) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

//===========================================================================
//---------------------------------------------------------------------------
// Allocates a T NxM matrix
//---------------------------------------------------------------------------
template<typename T>
Matrix<T>::Matrix(size_t _ni, size_t _nj) { // Custom Constructor
    int i;
    ni = _ni;
    nj = _nj; // numbers of rows and columns
    // allocate array of row pointers
    //    matrix = (T**) malloc((size_t)(ni*sizeof(T*)));
    matrix = new T*[ni];
    if (!matrix) {
        printf("Matrix: level 1 allocation error !\n");
        exit(1);
    }
    
    // assign block start to 1st row pointer
    // define row pointers spaced by row length
    for (i = 0; i < ni; i++) {
        matrix[i] = new T[nj];
        //        matrix[i] = (T*) malloc((size_t)(nj*sizeof(T)));
        //        matrix[i] = matrix[i-1] + nj;
    }
    if (!matrix[0]) {
        printf("Matrix: level 2 allocation error !\n");
        exit(2);
    }
}

//===========================================================================
//---------------------------------------------------------------------------
// Allocates a T NxM matrix
//---------------------------------------------------------------------------
template<typename T>
Matrix<T>::Matrix(size_t _ni) { // Custom Constructor
    int i;
    ni = _ni;
    nj = _ni; // numbers of rows and columns
    // allocate array of row pointers
    //    matrix = (T**) malloc((size_t)(ni*sizeof(T*)));
    matrix = new T*[ni];
    if (!matrix) {
        printf("Matrix: level 1 allocation error !\n");
        exit(1);
    }
    
    // assign block start to 1st row pointer
    for (i = 0; i < ni; i++) {
        matrix[i] = new T[nj];
        //        matrix[i] = matrix[i-1] + nj;
        //        matrix[0] = (T*) malloc((size_t)(ni*nj*sizeof(T)));
    }
    if (!matrix[0]) {
        printf("Matrix: level 2 allocation error !\n");
        exit(2);
    }
    // define row pointers spaced by row length
}

// Fills the matrix with zeros
template<typename T>
void Matrix<T>::zero() {
    int i, j;
    for (i=0; i < ni; i++) {
        for (j = 0; j < nj; ++j) {
            matrix[i][j] = static_cast<T>(0);
        }
    }
}
// Fills the matrix with num
template<typename T>
void Matrix<T>::value(T num) {
    int i, j;
    for (i=0; i < ni; i++) {
        for (j = 0; j < nj; ++j) {
            matrix[i][j] = static_cast<T>(num);
        }
    }
}

// Fills the matrix with random double numbers

template<typename T>
void Matrix<T>::rand(double start, double end) {
    int i, j;
    for (i=0; i < ni; i++) {
        for (j = 0; j < nj; ++j) {
            matrix[i][j] = static_cast<T>(generateRandomNum(start, end));
        }
    }
}

//---------------------------------------------------------------------------
// Prints the elements of matrix on the display
//---------------------------------------------------------------------------
template<typename T>
void Matrix<T>::print() {
    int i, j;
    puts("");
    for (i = 0; i <  ni; i++) {
        printf("%-3c", '|');
        for (j = 0; j < nj; j++) {
            if (matrix[i][j] < 0) {
                printf("%7.3lf",matrix[i][j]);
            } else {
                printf("%7.3lf",matrix[i][j]);
                
            }
        }
        printf("%5c\n", '|');
    }
    puts("");
}

//===========================================================================
//---------------------------------------------------------------------------
// Checks for equality
//---------------------------------------------------------------------------//
template<typename T>
bool Matrix<T>::operator == (const Matrix<T>& rhs) {
    //Check if the two matrices are the same size
    if ((ni != rhs.ni) && (nj != rhs.nj)) return false;
    for (int i = 0; i < ni; ++i) {
        for (int j = 0; j < nj; ++j) {
            if (rhs.matrix[i][j] != matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}

//===========================================================================
//---------------------------------------------------------------------------
// Prints the elements of transposed matrix a[1:n][1:m] on the display
//---------------------------------------------------------------------------
template<typename T>
Matrix<T> Matrix<T>::trans() {
    int i, j;
    Matrix<T> transposed(ni, nj);
    for (i = 0; i < ni; i++)  {
        for (j = 0; j < nj; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

//===========================================================================
//---------------------------------------------------------------------------
// Returns a pointer to the matrix, returns null if out of bounds
//---------------------------------------------------------------------------
template<typename T>
T* Matrix<T>::operator [](size_t index) const {
    if (index < 0 || index > ni) {
        if (index > nj) {
            return nullptr;
        }
        return nullptr;
    }
    return matrix[index];
}

//===========================================================================
//---------------------------------------------------------------------------
// Overload Object = operator
//---------------------------------------------------------------------------
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
    int i, j;
    ni = rhs.nj;
    nj = rhs.ni;
    for (i = 0; i < ni; i++) {
        for (j = 0; j < nj; j++) {
            matrix[i][j] = rhs.matrix[i][j];
        }
    }
    return *this;
}

//===========================================================================
//---------------------------------------------------------------------------
//    Matrix Scalar Operations
//---------------------------------------------------------------------------

// Multiply
template<typename T>
Matrix<T> Matrix<T>::operator*(T rhs) {
    int i, j;
    Matrix<T> result(ni, nj);
    for (i = 0; i < ni; i++) {
        for (j = 0; j < nj; j++) {
            result[i][j] = matrix[i][j] * rhs;
        }
    }
    return result;
}
// Multiply by
template<typename T>
Matrix<T>& Matrix<T>::operator*=(T rhs) {
    int i, j;
    for (i = 0; i < ni; i++) {
        for (j = 0; j < nj; j++) {
            matrix[i][j] *= rhs;
        }
    }
    return *this;
}

// Add
template<typename T>
Matrix<T> Matrix<T>::operator+(T rhs) {
    int i, j;
    Matrix<T> result(ni, nj);
    for (i = 0; i < ni; i++) {
        for (j = 0; j < nj; j++) {
            result[i][j] = matrix[i][j] + rhs;
        }
    }
    return result;
}
// Add by
template<typename T>
Matrix<T>& Matrix<T>::operator+=(T rhs) {
    int i, j;
    for (i = 0; i < ni; i++) {
        for (j = 0; j < nj; j++) {
            matrix[i][j] += rhs;
        }
    }
    return *this;
}

// Subtract
template<typename T>
Matrix<T> Matrix<T>::operator-(T rhs) {
    int i, j;
    Matrix<T> result(ni, nj);
    for (i = 0; i < ni; i++) {
        for (j = 0; j < nj; j++) {
            result[i][j] = matrix[i][j] - rhs;
        }
    }
    return result;
}
// Subtract by
template<typename T>
Matrix<T>& Matrix<T>::operator-=(T rhs) {
    int i, j;
    for (i = 0; i < ni; i++) {
        for (j = 0; j < nj; j++) {
            matrix[i][j] -= rhs;
        }
    }
    return *this;
}

// Divide
template<typename T>
Matrix<T> Matrix<T>::operator/(T rhs) {
    int i, j;
    Matrix<T> result(ni, nj);
    for (i = 0; i < ni; i++) {
        for (j = 0; j < nj; j++) {
            result[i][j] = matrix[i][j] / rhs;
        }
    }
    return result;
}
// Divide by
template<typename T>
Matrix<T>& Matrix<T>::operator/=(T rhs) {
    int i, j;
    for (i = 0; i < ni; i++) {
        for (j = 0; j < nj; j++) {
            matrix[i][j] /= rhs;
        }
    }
    return *this;
}
//===========================================================================


//===========================================================================
//---------------------------------------------------------------------------
//    Matrix Algebraic Operations
//---------------------------------------------------------------------------
// Addition
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& rhs) {
    Matrix<T> result(ni, nj);
    
    for (size_t i = 0; i < ni; i++) {
        for (size_t j = 0; j < nj; j++) {
            result[i][j] = this->matrix[i][j] + rhs[i][j];
        }
    }
    return result;
}
// Subtraction
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& rhs) {
    Matrix<T> result(ni, nj);
    
    for (size_t i = 0; i < ni; i++) {
        for (size_t j = 0; j < nj; j++) {
            result[i][j] = this->matrix[i][j] - rhs[i][j];
        }
    }
    return result;
}
// Multiplication
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs) {
    //Check if dimensions are compatible
    if (nj != rhs.ni) {
        perror("Matrices aren't compatible");
        exit(1);
    }
    Matrix<T> result(ni, rhs.nj);
    for (int i = 0; i < ni; ++i) {
        for (int j = 0; j < rhs.nj; ++j) {
            for (int k = 0; k < nj; ++k) {
                result.matrix[i][j] += matrix[i][k] * rhs.matrix[k][j];
            }
        }
    }
    return result;
}

// Swap function - pointer dereference version //
template<typename T>
void Matrix<T>::swap(T * a, T * b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

// Generate a random number between -1 and 1
template<typename T>
double Matrix<T>::generateRandomNum(double start, double end) {
    std::random_device r;
    std::default_random_engine el(r());
    std::uniform_real_distribution<double> uniform_dist(start, end);
    double num = uniform_dist(el);
    
    return num;
}

template <typename T>
void Matrix<T>::map(T (*func_callback)(T)) {
    int i, j;
    double (*f)(double) = func_callback;
    for (i = 0; i < ni; ++i) {
        for (j = 0; j < nj; ++j) {
            matrix[i][j] = (*f)(matrix[i][j]);
        }
    }
}

#endif /* mymatrix_h */
