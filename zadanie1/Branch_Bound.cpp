//
// Created by Maciej on 06.11.2022.
//
#include <climits>
#include <iostream>
#include "Branch_Bound.h"

using namespace std;

int Branch_Bound::find_min(vector<vector<int>> matrix, int i)
{
    int min = INT_MAX;
    for(int j= 0; j<matrix.size(); j++)
    {
        if(min>matrix[i][j] && i!=j)
            min = matrix[i][j];
    }
    return min;
}

int Branch_Bound::findSecMin(vector<vector<int>> matrix, int i)
{
    int first = INT_MAX;
    int second = INT_MAX;
    for(int j:matrix[i])
    {
        if(i==j)
            continue;

        if(matrix[i][j]<=first)
        {
            second = first;
            first = matrix[i][j];
        }
        else if(matrix[i][j] <=second && matrix[i][j]!=first)
            second = matrix[i][j];
    }
    return second;
}

void Branch_Bound::CheckLevel(vector<vector<int>> &matrix, int galaz, int koszt, int lvl, vector<int> droga, Branch_Bound BandB)
{
    // jezeli osiagnelismy ostatni poziom w drzewie
    if(lvl==matrix.size())
    {
        if(matrix[droga[lvl-1]][droga[0]])
        {
            int temp = koszt + matrix[droga[lvl-1]][droga[0]];

            if(temp < koszt)
            {
                path = droga;
                rozwiazanie = temp;
            }
        }
        return;
    }

    // kontynuujemy dla pozostalych poziomow
    for(int i=0; i<matrix.size(); i++)
    {
        if(matrix[droga[lvl-1]][i]!=0 && !visited[i])
        {
            int tmp = galaz;
            koszt+= matrix[droga[lvl-1]][i];

            if(lvl==1)
                galaz-= ((BandB.find_min(matrix, droga[lvl-1])+ BandB.find_min(matrix, i))/2);
            else
                galaz-= ((BandB.findSecMin(matrix, droga[lvl-1]) + BandB.find_min(matrix, i))/2);

            if(galaz + koszt < rozwiazanie)
            {
                droga[lvl] = i;
                visited[i] = true;

                CheckLevel(matrix, galaz, koszt, lvl+1, droga, BandB);
            }

            koszt-=matrix[droga[lvl-1]][i];
            galaz = tmp;

            for(int j=0; j<visited.size(); j++)
                visited[droga[j]]= false;
        }
    }
}

void Branch_Bound::TSP(vector<vector<int>> matrix)
{
    Branch_Bound BandB;
    int start =0;
    int size = matrix.size();
    path.resize(size+1);
    static vector<int> droga;
    droga.resize(size+1);
    int galaz = 0;

    for(int i=0; i<matrix.size(); i++)
        galaz+= find_min(matrix, i) + findSecMin(matrix, i);

    galaz = (galaz&1)? galaz/2 +1 : galaz/2;

    visited[start]=true;
    path.push_back(start);

    CheckLevel(matrix, galaz, 0, 1, droga, BandB);
}