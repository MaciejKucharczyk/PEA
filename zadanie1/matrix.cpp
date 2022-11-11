//
// Created by Maciej on 19.10.2022.
//

#include "matrix.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

Matrix::Matrix()
{
}

void Matrix::set_size(int s)
{
    size = s;
    matrix.resize(s);
}

Matrix::~Matrix()
= default;

vector<vector<int>> Matrix::return_matrix()
{
    return matrix;
}

void Matrix::read_from_file(string filename)
{
    matrix.clear();
    int val;
    fstream file;
    file.open(filename);
    if(file.is_open())
    {
        file >> size;
        matrix.resize(size);
        if(file.fail())
            cout << "File error - READ SIZE" << endl;
        else
            for(int i = 0; i < size; i++)
            {
                for(int j=0; j<size; j++)
                {
                    file >> val;
                    if(file.fail())
                    {
                        cout << "File error - READ DATA" << endl;
                        break;
                    }
                    else
                    {
                        matrix[i].push_back(val);
                        //cout<<"Dodaje element"<<i<<" "<<j<<endl;
                    }

                }
            }
        file.close();
    }
    else
        cout << "File error - OPEN" << endl;
}

void Matrix::print_matrix()
{
    for(int i=0; i< matrix.size(); i++)
    {
        for(int j=0; j< matrix.size(); j++)
            cout<< matrix[i][j] << " ";

        cout<<endl;
    }
}
