//
// Created by Maciej on 04.12.2022.
//

#include "Tabu.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

Tabu::Tabu() {

}

Tabu::~Tabu()= default;

void Tabu::Create_tabuList(int rozmiar)
{
    tabu_list.clear();
    for(int i=0; i<rozmiar; i++)
    {
        tabu_list.resize(rozmiar);
        for(int j=0; j<rozmiar; j++)
            tabu_list[i].resize(rozmiar);
    }
}

int M_val(vector<int> path, vector<vector<int>> m)
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

void Tabu::Update_tabulist(int x, int y, int rozmiar)
{
    for(int i=0; i<tabu_list.size(); i++)
        for(int j=0; j<tabu_list[i].size(); j++)
            if(tabu_list[i][j]>0)
                tabu_list[i][j]--;

    tabu_list[x][y]= rozmiar/2;
}

int Tabu::Silnia(int val)
{
    int result = 1;
    for(int i = val; i>1; i--)
        result+=i;
    return result;
}

void Tabu::Swap(int rozmiar, vector<vector<int>> m, vector<int> &curr_sol)
{
    int best_cost = M_val(curr_sol, m);
    for(int i=0; i<curr_sol.size(); i++)
        for(int j=0; j<curr_sol.size(); j++)
        {
            if(i==j)
                continue;

            if(tabu_list[i][j]==0)
            {
                int buff=curr_sol[i];
                curr_sol[i]=curr_sol[j];
                curr_sol[j] = buff;
                int cost = M_val(curr_sol, m);
                if(cost == -1)
                {
                    buff = curr_sol[i];
                    curr_sol[i] = curr_sol[j];
                    curr_sol[j] = buff;
                    break;
                }
               if(cost<best_cost)
                {
                    Update_tabulist(i,j, rozmiar);
                    cout<<"zamiana "<<i<<" "<<j<<endl;
                    continue;
                }
                else
                {
                    buff = curr_sol[i];
                    curr_sol[i] = curr_sol[j];
                    curr_sol[j] = buff;
                }
            }
            else
                continue;
        }
}

vector<int> Tabu::Rand_solution(vector<int> initial, int rozmiar)
{
    int koniec = Silnia(rozmiar-1);
    int licznik=0;
    while(next_permutation(initial.begin(), initial.end()))
    {
        if(licznik == koniec)
            return initial;
        licznik++;
    }
    return initial;
}

void Tabu::TSP(vector<vector<int>> matrix)
{
   // deklaracja list przechowujacych miasta
   /* curr_sol -> aktualnie badania sciezka
   * best_sol -> najkorzystniejsza znalezniona sciezka
   * cities -> posortowana lista miast (kolejnosc wg indeksow w macierzy) */
    vector<int> curr_sol, cities, best_sol;
    int rozmiar = matrix.size();
    Create_tabuList(rozmiar);

    for(int i=0; i<rozmiar; i++)
        if(i!=0)
            cities.push_back(i);

    best_sol.resize(rozmiar);
    curr_sol.resize(rozmiar);
    int best_cost, curr_cost; //best -> koszt najkorzystniejszej sciezki, curr -> koszt sciezki badanej
    //curr_sol = Rand_solution(cities, rozmiar);
    curr_sol = cities;
    random_shuffle(curr_sol.begin(), curr_sol.end());
    best_cost = M_val(curr_sol, matrix);
    best_sol = curr_sol;

    int licznik=rozmiar;
    while(licznik!=0)
    {
        Swap(rozmiar, matrix, (vector<int> &) curr_sol);
        curr_cost = M_val(curr_sol, matrix);
        if(curr_cost<best_cost)
        {
            best_cost = curr_cost;
            best_sol = curr_sol;
        }
        else
            licznik--;
    }

    cout<<"Sciezka: \n";
    cout<<"0 ";
    for(int city : best_sol)
        cout<<" -> "<<city<<" ";

    cout<<endl<<"Koszt: "<<best_cost<<endl;


}


