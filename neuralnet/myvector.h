//
//  vector.h
//  neuralnet
//
//  Created by Fabricio Bracht on 2019-07-02.
//  Copyright © 2019 Fabricio Bracht. All rights reserved.
//

#ifndef myvector_h
#define myvector_h

#include <iostream>
#include <iomanip>
//#include <random>
//#include <string>
//using namespace std;

template<typename T>
class Vector {
public:
    Vector();
    ~Vector();
    Vector(size_t);
    void resize(size_t); // Resizes the vector
//    virtual ostream& operator << (std::ostream &);
// Prints the Vector
    void initial(T);
    void random(T, T);
    bool isEmpty();
    size_t size() const { return last_filled_idx; };
    size_t cap() const { return capacity; };
    T get(size_t);
    void set(int, const T&);
    void push(T);

    // Operator overloading []
    T& operator[](size_t);
    const T& operator[](size_t) const;

    // Operator overloading, assignment operations
    Vector<T>& operator=(const Vector<T>& rhs);
    
    // Vector mathematical operations
    Vector<T>& operator+(const Vector<T>& rhs);
    Vector<T>& operator+=(const Vector<T>& rhs);
    Vector<T>& operator-(const Vector<T>& rhs);
    Vector<T>& operator-=(const Vector<T>& rhs);
    bool operator==(const Vector<T>& rhs);
    
    
    // Vector/scalar operations
    Vector<T> operator+(const T& rhs);
    Vector<T> operator+=(const T& rhs);
    Vector<T> operator-(const T& rhs);
    Vector<T> operator-=(const T& rhs);
    Vector<T> operator*(const T& rhs);
    Vector<T> operator*=(const T& rhs);
    Vector<T> operator/(const T& rhs);
    Vector<T> operator/=(const T& rhs);

private:
    void FreeVector(T *p);
    T* p;
    int64_t last_filled_idx;
    size_t capacity;
};

//===========================================================================
//---------------------------------------------------------------------------
// Default constructor for a vector with capacity 8
//---------------------------------------------------------------------------
template<typename T>
Vector<T>::Vector() {
    p = (T*) malloc((size_t) (8)*sizeof(T));
    last_filled_idx = -1;
    capacity = 8;
    if (!p) {
        perror("Vector: allocation error.\n");
        exit(1);
    }
}

//===========================================================================
//---------------------------------------------------------------------------
// Default destructor, calls FreeVector with imin = 0
//---------------------------------------------------------------------------
template<typename T>
Vector<T>::~Vector() {
    FreeVector(p);
}

//===========================================================================
//---------------------------------------------------------------------------
// Deallocates a double vector allocated with Vector, with offset imin
//---------------------------------------------------------------------------
template<typename T>
void Vector<T>::FreeVector(T *p) {
    free((void*) (p));
}
//===========================================================================
//---------------------------------------------------------------------------
// Allocates a double vector allocated with Vector, with custom size
//---------------------------------------------------------------------------
template<typename T>
Vector<T>::Vector(size_t size) {
    p = (T*) malloc((size_t) (size)*sizeof(T));
    last_filled_idx = -1;
    capacity = size;
    if (!p) {
        perror("Vector: allocation error.\n");
        exit(1);
    }
}
//===========================================================================
//---------------------------------------------------------------------------
// Deallocates a vector allocated with Vector, and allocates a new bigger one
//---------------------------------------------------------------------------
template<typename T>
void Vector<T>::resize(size_t new_size) {
    int i;
    T* new_p;
    new_p = (T*) malloc((size_t)(new_size*sizeof(T)));
    capacity = new_size;
    if (!new_p) {
        perror("Vector: allocation error.\n");
        exit(1);
    }
    if (last_filled_idx == -1) {
        delete[] p;
        p = new_p;
    } else {
        for (i = 0; i < last_filled_idx; ++i) {
            new_p[i] = p[i];
        }
        delete[] p;
        p = new_p;
    }
}
//===========================================================================
//---------------------------------------------------------------------------
// Prints the Vector - Not Working
//---------------------------------------------------------------------------
//template<typename T>
//ostream& operator<<(ostream &out, Vector<T>& vec) {
//    if (!vec.isEmpty()) {
//        perror("Cannot print empty vector");
//        exit(1);
//    }
//    out << "[";
//    for (int i = 0; i < vec.cap(); ++i) {
//        out << vec.get(i);
//    }
//    out << endl;
//    out.clear();
//
//    return out;
//}
//===========================================================================
//---------------------------------------------------------------------------
// Sets the initial values to value
//---------------------------------------------------------------------------
template<typename T>
void Vector<T>::initial(T value) {
    for (int i = 0; i < capacity; ++i) {
        p[i] = value;
        last_filled_idx++;
    }
}
//===========================================================================
//---------------------------------------------------------------------------
// Prints the Vector
//---------------------------------------------------------------------------
template<typename T>
void Vector<T>::random(T start, T end) {
    for (int i = 0; i < capacity; ++i) {
        p[i] = generateRandomNum(start, end);
        last_filled_idx++;
    }
}
//===========================================================================
//---------------------------------------------------------------------------
// Checks if the vector is empty
//---------------------------------------------------------------------------
template<typename T>
bool Vector<T>::isEmpty() {
    if (last_filled_idx == -1) {
        return true;
    }
    return false;
}
//===========================================================================
//---------------------------------------------------------------------------
// Getter function
//---------------------------------------------------------------------------
template<typename T>
T Vector<T>::get(size_t idx) {
    if (idx > last_filled_idx) {
        perror("Index out of bounds");
        exit(1);
    }
    return p[idx];
}
//===========================================================================
//---------------------------------------------------------------------------
// Setter function
//---------------------------------------------------------------------------
template <typename T>
void Vector<T>::set(int index, const T& value) {
    if (index < 0 || index >= last_filled_idx) {
        perror("set: index out of range");
        exit(1);
    }
    p[index] = value;
}
//===========================================================================
//---------------------------------------------------------------------------
// Pushes values to the back and resizes if necessary
//---------------------------------------------------------------------------
template<typename T>
void Vector<T>::push(T value) {
    if (last_filled_idx == capacity - 1) {
//        T *new_array;
        size_t new_capacity = (capacity * 2);
//        new_array = new T[new_capacity];
//        for (int i = 0; i < capacity; i++) {
//            new_array[i] = p[i];
//        }
//        delete[] p;
        capacity = new_capacity;
//        p = new_array;
        resize(new_capacity);
    }
    last_filled_idx = last_filled_idx + 1;
    p[last_filled_idx] = value;
}


template<typename T>
T& Vector<T>::operator[](size_t idx) {
    if (idx < 0 || idx > last_filled_idx) {
        perror("Index out of boundary");
        exit(1);
    }
    return p[idx];
}

template<typename T>
const T& Vector<T>::operator[](size_t idx) const {
    if (idx < 0 || idx > last_filled_idx) {
        perror("Index out of boundary");
        exit(1);
    }
    return p[idx];
}


template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs) {
    if (&rhs == this)
        return *this;
    
    for (int i = 0; i <= rhs.last_filled_idx; ++i) {
        p[i] = rhs.p[i];
    }
    last_filled_idx = rhs.last_filled_idx;
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator+(const Vector<T>& rhs) {
    if (capacity != rhs.cap()) {
        perror("Vectors have incompatible sizes");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= rhs.size(); ++i) {
        p[i] = p[i] + rhs[i];
    }
    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator+(const T& rhs) {
    for (int i = 0; i <= last_filled_idx; ++i) {
        p[i] += rhs;
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& rhs) {
    if (capacity != rhs.cap()) {
        perror("Vectors have incompatible sizes");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= rhs.size(); ++i) {
        p[i] += rhs[i];
    }
    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator+=(const T& rhs) {
    for (int i = 0; i <= last_filled_idx; ++i) {
        p[i] += rhs;
    }
    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator-(const T& rhs) {
    for (int i = 0; i <= last_filled_idx; ++i) {
        p[i] -= rhs;
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& rhs) {
    if (capacity != rhs.cap()) {
        perror("Vectors have incompatible sizes");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= rhs.size(); ++i) {
        p[i] -= rhs[i];
    }
    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator-=(const T& rhs) {
    for (int i = 0; i <= last_filled_idx; ++i) {
        p[i] -= rhs;
    }
    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator*(const T& rhs) {
    for (int i = 0; i <= last_filled_idx; ++i) {
        p[i] *= rhs;
    }
    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator*=(const T& rhs) {
    for (int i = 0; i <= last_filled_idx; ++i) {
        p[i] *= rhs;
    }
    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator/(const T& rhs) {
    for (int i = 0; i <= last_filled_idx; ++i) {
        p[i] /= rhs;
    }
    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator/=(const T& rhs) {
    for (int i = 0; i <= last_filled_idx; ++i) {
        p[i] /= rhs;
    }
    return *this;
}

template<typename T>
bool Vector<T>::operator==(const Vector<T>& rhs) {
    if (last_filled_idx != rhs.size()) {
        return false;
    }
    for (int i = 0; i < rhs.size(); ++i) {
        if (p[i] != rhs[i]){
            return false;
        }
    }
    return true;
}

template<typename T>
void printVec(Vector<T>& vec) {
    puts("");
    printf("%3c", '[');
    for (int i = 0; i < vec.cap(); ++i) {
        printf("%7.3f", vec.get(i));
        if (i != vec.size()) {
            printf(", ");
        }
    }
    printf("%3c", ']');
    puts("");
}


#endif /* myvector_h */
