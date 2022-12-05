//
// Created by Maciej on 04.12.2022.
//
#include <vector>

#ifndef ZADANIE2_TABU_H
#define ZADANIE2_TABU_H

using namespace std;

/*struct TMove{
    int K, start, end;
};*/


class Tabu {
private:
    //vector<vector<int>> tabu_list;
public:
    Tabu();
    ~Tabu();
    vector<vector<int>> tabu_list;
    void TSP(vector<vector<int>> matrix);

    vector<int> Rand_solution(vector<int> initial, int rozmiar);

    void Swap(int rozmiar, vector<vector<int>> m, vector<int> &curr_sol);

    void Update_tabulist(int x, int y, int rozmiar);

    void Create_tabuList(int rozmiar);

    int Silnia(int val);
};


#endif //ZADANIE2_TABU_H
