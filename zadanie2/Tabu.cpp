//
// Created by Maciej on 04.12.2022.
//

#include "Tabu.h"
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

Tabu::Tabu() {}

Tabu::~Tabu()= default;

void Tabu::SetStop(int s)
{
    if(stop==0)
        stop = s;
}


void Tabu::Create_tabuList(int rozmiar)
{
    //tabu_list.clear();
    for(int i=0; i<rozmiar; i++)
    {
        tabu_list.resize(rozmiar);
        for(int j=0; j<rozmiar; j++)
            tabu_list[i].resize(i+1);
    }
}

int Tabu::M_val(vector<int> &path, vector<vector<int>> &m)
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

void Tabu::Update_tabulist(int x, int y, int rozmiar)
{
    for(int i=0; i<tabu_list.size(); i++)
        for(int j=0; j<tabu_list[i].size(); j++)
            if(tabu_list[i][j]>0)
                tabu_list[i][j]--;

    if(x>y)
        tabu_list[x][y]= rozmiar;
    else
        tabu_list[y][x] = rozmiar;
}

bool Tabu::Swap(int rozmiar, vector<vector<int>> &m, vector<int> &curr_sol, int best_cost)
{
   int initial_best = best_cost;
   for (int i = 0; i < curr_sol.size(); i++)
        for (int j = 0; j < curr_sol.size(); j++)
        {
            if (i == j)
                continue;

            int buff=curr_sol[i];
            curr_sol[i]=curr_sol[j];
            curr_sol[j] = buff;

            if(i>j)
            {
                if (tabu_list[i][j] == 0)
                {
                    int cost = M_val(curr_sol, m);
                    if(best_cost>cost)
                    {
                        Update_tabulist(i, j, rozmiar);
                        best_cost = cost;
                        //return true;
                    }
                    else
                    {
                        buff=curr_sol[i];
                        curr_sol[i]=curr_sol[j];
                        curr_sol[j] = buff;
                        //return false;
                    }
                }
            }
            else
                if (tabu_list[j][i] == 0)
                {
                    int cost = M_val(curr_sol, m);
                    if(best_cost>cost)
                    {
                        Update_tabulist(i, j, rozmiar);
                        best_cost = cost;
                        //return true;
                    }
                    else
                    {
                        buff=curr_sol[i];
                        curr_sol[i]=curr_sol[j];
                        curr_sol[j] = buff;
                        //return false;
                    }
                }

        }
   if(initial_best>best_cost) // jezeli znaleziono nizszy koszt, to zwracamy true, w p.p false
       return true;
   else
       return false;
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
    // zapisujemy miasta w kolejnosci do sciezki, a potem losujemy miasta w sciezce
    curr_sol = cities;
    shuffle(curr_sol.begin(), curr_sol.end(), std::mt19937(std::random_device()()));
    best_cost = M_val(curr_sol, matrix);
    best_sol = curr_sol;
    //kryterium stopu
    SetStop(rozmiar); // jezeli kryterium nie zostalo wprowadzone w menu, to domyslna wartoscia jest 'rozmiar'

    int licznik=int(pow(pow(rozmiar*rozmiar,stop),stop));

    while(licznik!=0)
    {
        bool is_changed = Swap(rozmiar, matrix, curr_sol, best_cost);
       curr_cost = M_val(curr_sol, matrix);
       // jezeli znaleziono lepsza sciezke, to zapisujemy ją
       if(is_changed)
       {
           best_sol = curr_sol;
           best_cost = M_val(best_sol, matrix);
           licznik = stop; // zwiększamy licznik do wartosci pocz. kontynuujemy poszukiwanie
       }
       else
       {
           licznik--; // zmniejszamy licznik, jezeli poszukiwanie zajmie za duzo iteracji,
                    // to zwracamy najlepsze znalezione rozwiazanie
       }
    }

    cout<<"Sciezka: \n";
    cout<<"0 ";
    for(int city : best_sol)
        cout<<" -> "<<city<<" ";

    cout<<endl<<"Koszt: "<<best_cost<<endl;


}


