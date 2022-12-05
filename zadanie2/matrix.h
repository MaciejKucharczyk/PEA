//
// Created by Maciej on 04.12.2022.
//

#ifndef ZADANIE2_MATRIX_H
#define ZADANIE2_MATRIX_H
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
#endif //ZADANIE2_MATRIX_H
