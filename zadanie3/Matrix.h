//
// Created by speed on 11.01.2023.
//

#ifndef ZADANIE3_MATRIX_H
#define ZADANIE3_MATRIX_H

#include <string>
#include <vector>

using namespace std;

class Matrix {
private:
    vector<vector<int>> matrix;
    // int size;
    //int* stos = new int[size];
public:
    int size=0;
    Matrix(); //(int s)
    ~Matrix();
    vector<vector<int>> return_matrix();
    void read_from_file(string filename);
    void print_matrix();
};


#endif //ZADANIE3_MATRIX_H
