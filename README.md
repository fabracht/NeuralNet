# NeuralNet

This is a work in progress. A lot of it is based on the book "Make your Own Neural Network", by Tariq Rashid
The book implements a neural network in python. So, I decided to write my own neural network in c++
As any python to c++ translation, nothing is straight forward. If you've never done it before, you will not
understand what I meant by that.
The final project will identify hand written numbers (hopefully).

This project was written to implement a very simple neural network from scratch in c++
It contains a templated matrix class, which implements a matrix by using T**
It contains a vector class, which is currently not being used for anything. But it might.
It contains a linked list class, which is also not being used.
The neural network itself is currently written with a mix of matrices in main and a struct called Neural
The Neural Struct describes the amount of input nodes, hidden nodes and output nodes. It contains a constructor
and 2 methods (query() and train())
Query() is written but I haven't had time to check yet if it's doing what it's supposed to do.
Train() will be written in a near future.
