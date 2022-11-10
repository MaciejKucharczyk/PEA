//
// Created by Maciej on 06.11.2022.
//

#ifndef PEA_BRANCH_BOUND_H
#define PEA_BRANCH_BOUND_H
#include <vector>

using namespace std;

class Branch_Bound {
public:
    static int rozwiazanie;
    static vector<int> path;
    static vector<bool> visited;

    static void CheckLevel(vector<vector<int>> &matrix, int galaz, int koszt, int lvl, vector<int> droga, Branch_Bound BandB);
    void TSP(vector<vector<int>> matrix);
    int find_min(vector<vector<int>> matrix, int i);
    int findSecMin(vector<vector<int>> matrix, int i);
};

#endif //PEA_BRANCH_BOUND_H
