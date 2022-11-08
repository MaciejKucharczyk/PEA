//
// Created by Maciej on 19.10.2022.
//

#ifndef PEA_MATRIX_H
#define PEA_MATRIX_H
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
    Matrix(int s);
    ~Matrix();
    vector<vector<int>> return_matrix();
    void read_from_file(string filename);
    void print_matrix();

};

/*vector<vector<int>> make_matrix(int size);

void read_from_file(string filename, vector<vector<int>> matrix);

void print_matrix(vector<vector<int>> matrix);*/


#endif //PEA_MATRIX_H
