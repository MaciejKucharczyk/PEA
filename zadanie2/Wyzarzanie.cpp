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
        koszt += m[j][path[city]];
        j=path[city];
    }
    koszt+=m[j][0];
    return koszt;
}

bool Wyzarzanie::Swap(int rozmiar, vector<vector<int>> m, vector<int> &curr_sol, double t, int best_cost)
{
    srand(time(NULL));
    //int best_cost = M_val(curr_sol, m);
    int initial_best = best_cost;
    for(int i=0; i<curr_sol.size(); i++)
        for(int j=0; j<curr_sol.size(); j++)
        {
            if(i==j)
                continue;

            int buff=curr_sol[i];
            curr_sol[i]=curr_sol[j];
            curr_sol[j] = buff;

            int cost = M_val(curr_sol, m);
            if(best_cost>cost)
            {
                best_cost = cost;
                //cout<<"zamiana\n";
            }
            else
            {
                double s = ((double) rand() / (RAND_MAX));
                double pr = exp((best_cost-cost)/t);
                if(s<pr)
                {
                    //cout<<"niekorzystna zamiana\n";
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
    if(initial_best>best_cost) // jezeli znaleziono nizszy koszt, to zwracamy true, w p.p false
        return true;
    else
        return false;
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
        bool is_changed = Swap(rozmiar, matrix, curr_sol, T, best_cost);
        curr_cost = M_val(curr_sol, matrix);
        // jezeli znaleziono lepsza sciezke, to zapisujemy ją
        if(is_changed)
        {
            best_cost = curr_cost;
            best_sol = curr_sol;
            licznik = stop; // zwiększamy licznik do wartosci pocz. kontynuujemy poszukiwanie
        }
        else
        {
            licznik--; // zmniejszamy licznik, jezeli poszukiwanie zajmie za duzo iteracji,
            // to zwracamy najlepsze znalezione rozwiazanie
            double dT = pow(a, stop-licznik)*T;
            T-=dT;
        }
    }

    cout<<"Sciezka: \n";
    cout<<"0 ";
    for(int city : best_sol)
        cout<<" -> "<<city<<" ";

    cout<<endl<<"Koszt: "<<best_cost<<endl;


}