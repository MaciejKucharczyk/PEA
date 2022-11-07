//
// Created by Maciej on 06.11.2022.
//

#ifndef PEA_BRANCH_BOUND_H
#define PEA_BRANCH_BOUND_H
#include <vector>

using namespace std;

class Branch_Bound {
public:
    int final_res = INT_MAX;
    vector<int> final_path;
    static vector<bool> visited;
    static void branch_bound(vector<vector<int>>, int);
    //void reduction(vector<vector<int>>);
    int find_min(vector<vector<int>>, int);
    void copyToFinal(vector<int> m);

    int findSecMin(vector<vector<int>>, int);

    void TSPRec(vector<vector<int>> tab, int curr_bound, int curr_weight, int level, vector<int> path);
};

#endif //PEA_BRANCH_BOUND_H
