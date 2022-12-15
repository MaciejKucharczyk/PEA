//
// Created by Maciej on 13.12.2022.
//

#ifndef ZADANIE2_WYZARZANIE_H
#define ZADANIE2_WYZARZANIE_H


#include <vector>

using namespace std;

class Wyzarzanie {
public:
    int stop_SA=5;
    int M_val(std::vector<int> path, vector<vector<int>> m);

    void TSP(vector<vector<int>> matrix);

    bool Swap(int rozmiar, vector<vector<int>> m, vector<int> &curr_sol, double t, int best_cost);

    long long int read_QPC();
};


#endif //ZADANIE2_WYZARZANIE_H
