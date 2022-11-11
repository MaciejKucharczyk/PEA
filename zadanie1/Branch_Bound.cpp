//
// Created by Maciej on 06.11.2022.
//
#include <climits>
#include <iostream>
#include "Branch_Bound.h"

using namespace std;

Branch_Bound::Branch_Bound()
{
    rozwiazanie = INT_MAX;
}

void Branch_Bound::setSize(int size)
{
    path.resize(size + 1);
    visited.resize(size);
}

Branch_Bound::~Branch_Bound(){}

void Branch_Bound::print_result(int koszt, vector<int> path)
{
    cout<<"Koszt: "<<koszt<<endl;
    for(int i=0; i<path.size(); i++)
        cout<<" -> " <<path[i];
    cout<<endl;
}


int Branch_Bound::find_min(vector<vector<int>> matrix, int i)
{
    int min = INT_MAX;
    for (int j = 0; j < matrix.size(); j++)
    {
        if (min > matrix[i][j] && i != j)
            min = matrix[i][j];
    }
    return min;
}

int Branch_Bound::findSecMin(vector<vector<int>> matrix, int i)
{
    int first = INT_MAX;
    int second = INT_MAX;
    for (int j =0; j<matrix[i].size(); j++)
    {
        if (i == j)
            continue;

        if (matrix[i][j] <= first)
        {
            second = first;
            first = matrix[i][j];
        }
        else if (matrix[i][j] <= second && matrix[i][j] != first)
            second = matrix[i][j];
    }
    return second;
}

void Branch_Bound::CheckLevel(vector<vector<int>>& matrix, int galaz, int koszt, int lvl, vector<int> &droga, Branch_Bound &BandB, int &rozwiazanie, vector<bool>& visited, vector<int>& path)
{
    // jezeli osiagnelismy ostatni poziom w drzewie
    if (lvl == matrix.size())
    {
        if (matrix[droga[lvl - 1]][droga[0]]!=0)
        {
            int temp = koszt + matrix[droga[lvl - 1]][droga[0]];

            if (temp < BandB.rozwiazanie)
            {
                BandB.path = droga;
                BandB.rozwiazanie = temp;
            }
        }
        return;
    }

    // kontynuujemy dla pozostalych poziomow
    for (int i = 0; i < matrix.size(); i++)
    {
        if (matrix[droga[lvl - 1]][i] != 0 && !BandB.visited[i])
        {
            int tmp = galaz;
            koszt += matrix[droga[lvl - 1]][i];

            if (lvl == 1)
                galaz -= ((BandB.find_min(matrix, droga[lvl - 1]) + BandB.find_min(matrix, i)) / 2);
            else
                galaz -= ((BandB.findSecMin(matrix, droga[lvl - 1]) + BandB.find_min(matrix, i)) / 2);

            if (galaz + koszt < BandB.rozwiazanie)
            {
                droga[lvl] = i;
                BandB.visited[i] = true;

                CheckLevel(matrix, galaz, koszt, lvl+1, droga, BandB, BandB.rozwiazanie, BandB.visited, BandB.path);
            }

            koszt -= matrix[droga[lvl - 1]][i];
            galaz = tmp;

            for (int j = 0; j < visited.size(); j++)
                BandB.visited[droga[j]] = false;

            for(int j=0; j<=lvl-1; j++)
                visited[droga[j]]=true;
        }
    }
}

void Branch_Bound::TSP(vector<vector<int>> matrix)
{
    int size = matrix.size();
    Branch_Bound BandB;
    BandB.setSize(size);
    int start = 0;
    static vector<int> droga;
    droga.resize(size + 1);
    int ogranicznik = 0;

    for (int i = 0; i < matrix.size(); i++)
        ogranicznik += BandB.find_min(matrix, i) + BandB.findSecMin(matrix, i);

    ogranicznik = (ogranicznik & 1) ? ogranicznik / 2 + 1 : ogranicznik / 2;

    BandB.visited[start] = true;
    BandB.path.push_back(start);

    CheckLevel(matrix, ogranicznik, 0, 1, droga, BandB, BandB.rozwiazanie, BandB.visited, BandB.path);
    //BandB.path = droga;
    BandB.print_result(BandB.rozwiazanie, BandB.path);
}