//
// Created by Maciej on 06.11.2022.
//

#include <climits>
#include <cstring>
#include <iostream>
#include "Branch_Bound.h"

using namespace std;

void Branch_Bound::copyToFinal(vector<int> m)
{
    final_path = m;
}

int Branch_Bound::find_min(vector<vector<int>> tab, int i)
{
    int min = INT_MAX;
    for(int j= 0; j<tab.size(); j++)
    {
        if(min>tab[i][j] && i!=j)
            min = tab[i][j];
    }
    return min;
}

int Branch_Bound::findSecMin(vector<vector<int>> tab, int i)
{
    int first = INT_MAX;
    int second = INT_MAX;
    for(int j:tab[i])
    {
        if(i==j)
            continue;

        if(tab[i][j]<=first)
        {
            second = first;
            first = tab[i][j];
        }
        else if(tab[i][j] <=second && tab[i][j]!=first)
            second = tab[i][j];
    }
    return second;
}

void Branch_Bound::TSPRec(vector<vector<int>> tab, int curr_bound, int curr_weight, int level, vector<int> path)
{
    if(level ==tab.size())
    {
        if(tab[path[level - 1]][path[0]]!=0)
        {
            int curr_res = curr_weight + tab[path[level - 1]][path[0]];

            if(curr_res<final_res)
            {
                copyToFinal(path);
                final_res = curr_res;
            }
        }
        return;
    }

    for(int i = 0; i<tab.size(); i++)
    {
        int temp;
        if(tab[path[level-1]][i]!=0 && visited[i]==false)
        {
            temp = curr_bound;
            curr_weight +=tab[path[level-1]][i];

            if(level==1)
                curr_bound-=((find_min(tab, path[level-1])+ find_min(tab, i))/2);
            else
                curr_bound-=((findSecMin(tab, path[level-1])+ find_min(tab, i))/2);
        }

        if (curr_bound + curr_weight <final_res)
        {
            path[level]=i;
            visited[i]= true;

            TSPRec(tab, curr_bound, curr_weight, level+1, path);
        }

        curr_weight -= tab[path[level-1]][i];
        curr_bound = temp;

        for(int k=0; k<tab.size(); k++)
            visited[k]=false;
        for(int k=0; k<tab.size(); k++)
            visited[path[k]]=true;
    }
}

void Branch_Bound::branch_bound(vector<vector<int>> macierz, int rozmiar)
{
    vector<vector<int>> matrix = macierz;
    //static vector<int> final_path;
    visited.resize(macierz.size());
    for(auto && i : visited)
        i = false;
    //int curr_path[macierz.size()+1];
    vector<int> path;
    path.resize(macierz.size());

    int curr_bound = 0;

    for(int i:path)
        path[i]=-1;

    for(int i=0; i<matrix.size(); i++)
        curr_bound+=(find_min(macierz, i)+ findSecMin(macierz, i));
    curr_bound = (curr_bound&1)? curr_bound/2 +1 : curr_bound/2;

    visited[0]= true;
    path[0]=0;

    TSPRec(macierz, curr_bound, 0, 1, path);

    cout<<"Koszt: "<<final_res<<endl;
    cout<<"Droga: \n";
    for(int i=0; i<path.size(); i++)
    {
        cout<<" -> "<<path[i];
    }

}

