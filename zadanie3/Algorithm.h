//
// Created by speed on 11.01.2023.
//

#ifndef ZADANIE3_ALGORITHM_H
#define ZADANIE3_ALGORITHM_H


#include <vector>
#include <algorithm>

using namespace std;

struct Chromosome {
    vector<int> path;
    double fitness;

    Chromosome(vector<int> &cities);

    int calculateFitness(vector<vector<int>> &m);
};

class Algorithm {
public:
    int stop = 10;
    int initial_size = 10;
    int size_of_pop = initial_size;
    double mutation_rate = 0.01;
    const double cross_over_rate = 0.7;
    const int selection_min = 10;

    //vector<vector<int>> population;
    Algorithm();

    static long long int read_QPC();

    void TSP(std::vector<vector<int>> matrix);

    Chromosome M_val(vector<vector<int>> &m, vector<Chromosome> &population);

    void Create_population(vector<vector<int>> &m, vector<int> &cities, int size, vector<Chromosome> &population);

    void CrossOver(int &rozmiar, vector<Chromosome> &population);

    void Mutation(int &rozmiar, vector<Chromosome> &population);

    void Selection(int &rozmiar, vector<Chromosome> &population, Chromosome best, vector<vector<int>> &m);

    bool CkeckTime(long long int start, long long int frequency);
};


#endif //ZADANIE3_ALGORITHM_H
