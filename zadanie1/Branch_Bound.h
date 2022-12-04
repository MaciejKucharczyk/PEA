//
// Created by Maciej on 06.11.2022.
//

#ifndef PEA_BRANCH_BOUND_H
#define PEA_BRANCH_BOUND_H
#include <vector>

using namespace std;

class Branch_Bound {
public:
    int rozwiazanie;
    vector<int> path;
    vector<bool> visited;

    Branch_Bound();
    ~Branch_Bound();
    static void CheckLevel(vector<vector<int>>& matrix, int galaz, int koszt, int lvl, vector<int> &droga, Branch_Bound& BandB, int &rozwiazanie, vector<bool> &visited, vector<int> &path);
    static void TSP(vector<vector<int>> matrix);
    int find_min(vector<vector<int>> matrix, int i);
    int findSecMin(vector<vector<int>> matrix, int i);
    void print_result(int koszt, vector<int> path);

    void setSize(int size);
};

#endif //PEA_BRANCH_BOUND_H
