//
// Created by Maciej on 13.12.2022.
//

#ifndef ZADANIE2_WYZARZANIE_H
#define ZADANIE2_WYZARZANIE_H


#include <vector>

using namespace std;

class Wyzarzanie {
public:
    int M_val(std::vector<int> path, vector<vector<int>> m);

    void TSP(vector<vector<int>> matrix);

    void Swap(int rozmiar, vector<vector<int>> m, vector<int> &curr_sol, int t);
};


#endif //ZADANIE2_WYZARZANIE_H