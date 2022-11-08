//
// Created by Maciej on 29.10.2022.
//

#include "M_Generator.h"
#include <random>

using namespace std;


vector<vector<int>> M_Generator::generate_matrix(int size)
{
    srand(time(NULL));
    vector<vector<int>> matrix;
    matrix.resize(size);
    int val=0;
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
        {
            if(i==j)
                matrix[i][j]=0;
            else
            {
                val=rand()%100;
                matrix[i][j] = val;
            }
        }
    return matrix;
}
