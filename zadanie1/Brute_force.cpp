//
// Created by Maciej on 29.10.2022.
//

#include "Brute_force.h"
#include <bits/stdc++.h>

void Brute_force::shortest_path(vector<vector<int>> macierz)
{
    int rozmiar = macierz.size();
    int start = 0;
    int shortest_path = INT_MAX;
    vector <int> cities;
    vector <int> path;

    for(int i=0; i<rozmiar; i++)
    {
        if(i!=start)
            cities.push_back(i);
    }

    path.push_back(start); // to i tak nic nie zmienia :/

    while(next_permutation(cities.begin(), cities.end()))
    {
        bool stop = false;
        int koszt = 0;
        int j = start;

        for(int city : cities)
        {
            if(macierz[city][j]==0)
            {
                stop = true;
                break;
            }
            koszt+=macierz[city][j];
           j = city;
        }
        if(stop)
            continue;
        koszt+= macierz[start][j];

        if(shortest_path>koszt)
        {
            shortest_path = koszt;
            path = cities;
            path.push_back(start);
            //for(int city: cities)
            //  path.push_back(city);
        }
    }
    cout<<"Koszt najkorzystniejszej drogi: "<<shortest_path<<endl;
    cout<<"Droga: "<<endl<<0; //wyswietlamy zero, poniewaz nie ma go na poczatku w 'path'
    for(int i: path)
        cout<<" -> "<<i;
    cout<<endl;
}
