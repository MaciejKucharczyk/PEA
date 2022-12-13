//
// Created by Maciej on 13.12.2022.
//

#include "Wyzarzanie.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

int Wyzarzanie::M_val(vector<int> path, vector<vector<int>> m)
{
    int j = 0;
    int koszt = 0;
    for(int city=0; city<path.size(); city++)
    {
        koszt += m[j][city];
        j=city;
    }
    koszt+=m[j][0];
    return koszt;
}

void Wyzarzanie::Swap(int rozmiar, vector<vector<int>> m, vector<int> &curr_sol, int t)
{
    srand(time(NULL));
    int best_cost = M_val(curr_sol, m);
    for(int i=0; i<curr_sol.size(); i++)
        for(int j=0; j<curr_sol.size(); j++)
        {
            if(i==j)
                continue;

            int buff=curr_sol[i];
            curr_sol[i]=curr_sol[j];
            curr_sol[j] = buff;
            int cost = M_val(curr_sol, m);
            if(cost<=best_cost)
            {
                cout<<"zamiana "<<i<<" "<<j<<endl;
                best_cost = cost;
                continue;
            }
            else
            {
                double s = ((double) rand() / (RAND_MAX)) + 1;
                double pr = exp((best_cost-cost)/t);
                if(s<pr)
                {
                    cout<<"niekorzystna zamiana "<<i<<" "<<j<<endl;
                    best_cost = cost;
                    continue;
                }
                else
                {
                    buff = curr_sol[i];
                    curr_sol[i] = curr_sol[j];
                    curr_sol[j] = buff;
                }
            }
        }
}


void Wyzarzanie::TSP(vector<vector<int>> matrix)
{
    // deklaracja list przechowujacych miasta
    /* curr_sol -> aktualnie badania sciezka
    * best_sol -> najkorzystniejsza znalezniona sciezka
    * cities -> posortowana lista miast (kolejnosc wg indeksow w macierzy) */
    vector<int> curr_sol, cities, best_sol;
    double a = 0.99;
    double T=1000; // temperatura poczatkowa
    int rozmiar = matrix.size();

    for(int i=0; i<rozmiar; i++)
        if(i!=0)
            cities.push_back(i);

    best_sol.resize(rozmiar);
    curr_sol.resize(rozmiar);
    int best_cost, curr_cost; //best -> koszt najkorzystniejszej sciezki, curr -> koszt sciezki badanej
    //curr_sol = Rand_solution(cities, rozmiar);
    curr_sol = cities;
    shuffle(curr_sol.begin(), curr_sol.end(), std::mt19937(std::random_device()()));
    best_cost = M_val(curr_sol, matrix);
    best_sol = curr_sol;
    //epoka
 //   SetStop(rozmiar); // jezeli kryterium nie zostalo wprowadzone w menu, to domyslna wartoscia jest 'rozmiar'
    int stop = rozmiar;

    int licznik=stop;
    while(licznik!=0)
    {
        Swap(rozmiar, matrix, (vector<int> &) curr_sol, T);
        curr_cost = M_val(curr_sol, matrix);
        if(curr_cost<best_cost)
        {
            best_cost = curr_cost;
            best_sol = curr_sol;
            licznik=stop;
        }
        else
            licznik--; // zmniejszamy licznik, jezeli "utknelismy" na jednym rozwiazaniu

            double dT = pow(a, stop-licznik)*T;
            T-=dT;
    }

    cout<<"Sciezka: \n";
    cout<<"0 ";
    for(int city : best_sol)
        cout<<" -> "<<city<<" ";

    cout<<endl<<"Koszt: "<<best_cost<<endl;


}