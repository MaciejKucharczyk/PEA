//
// Created by Maciej on 04.12.2022.
//
#include <vector>

#ifndef ZADANIE2_TABU_H
#define ZADANIE2_TABU_H

using namespace std;

class Tabu {
public:
    int stop=0;
    Tabu();
    ~Tabu();
    vector<vector<int>> tabu_list;
    void TSP(vector<vector<int>> matrix);

    bool Swap(int rozmiar, vector<vector<int>> &m, vector<int> &curr_sol, int best_sol);

    void Update_tabulist(int x, int y, int rozmiar);

    void Create_tabuList(int rozmiar);

    void SetStop(int s);

    int M_val(vector<int> &path, vector<vector<int>> &m);
};


#endif //ZADANIE2_TABU_H
