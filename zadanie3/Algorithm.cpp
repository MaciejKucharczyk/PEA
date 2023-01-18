//
// Created by speed on 11.01.2023.
//

#include "Algorithm.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <random>


using namespace std;

//-------------------------------------------------------------------------
long long int Algorithm::read_QPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}
//-------------------------------------------------------------------------


Chromosome::Chromosome(vector<int> &cities) {
    path.resize(cities.size());
    path = cities;
    random_shuffle(path.begin() + 1, path.end());
    fitness = 0;
}

int Chromosome::calculateFitness(vector<vector<int>> &m) {
    int totalDistance = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        totalDistance += m[path[i]][path[i + 1]]; // TODO: seg fault
    }
    totalDistance += m[path[path.size() - 1]][path[0]];
    fitness = 1 / double(totalDistance);
    return totalDistance;
}

// =====================================================================

Algorithm::Algorithm()
{
    vector<Chromosome> population;
}

Chromosome Algorithm::M_val(vector<vector<int>> &m, vector<Chromosome> &population)
{
/*    int j = 0;
    int koszt = 0;
    for(int city=0; city<path.size(); city++)
    {
        koszt += m[j][path[city]];
        j=path[city];
    }
    koszt+=m[j][0];
    return koszt;*/
    Chromosome best = *new Chromosome(population[0]);
    double best_fit = 0;
    for(int i=0; i < population.size(); i++)
    {
        if(population[i].fitness > best_fit)
        {
            best = population[i];
        }
    }
    return best;

}

void Algorithm::Create_population(vector<vector<int>> &m, vector<int> &cities, int size, vector<Chromosome> &population)
{
    for(int i=0; i < size_of_pop; i++)
    {
        population.push_back(Chromosome(cities));
    }
}

void Algorithm::CrossOver(int &rozmiar, vector<Chromosome> &population)
{
    for(int i=0; i<size_of_pop; i++)
    {
        if((double) rand() / RAND_MAX < cross_over_rate)
        {
            int rand_Index = rand() % size_of_pop;
            int rand_City = rand() % rozmiar;
            Chromosome offspring = population[i]; // kopiujemy jeden z chromosomow w populacji do nowego potommka

            for(int j=rand_City+1; j < rozmiar; j++) // petla zamieniajace miasta z innym chromosomem rodzicem
            {
                int city = population[rand_Index].path[j];
                auto it = find(offspring.path.begin(), offspring.path.end(), city);

                int idx = distance(offspring.path.begin(), it);
                swap(offspring.path[j], offspring.path[idx]);
            }
            population.push_back(offspring);
            size_of_pop = population.size();
        }
    }
}

void Algorithm::Mutation(int &rozmiar, vector<Chromosome> &population)
{
    for(int i = 0; i < size_of_pop; i++)
    {
        if((double) rand() / RAND_MAX < mutation_rate)
        {
            //int rand_id = rand() % size_of_pop;
            int city1, city2;
            do {
                city1 = rand() % (rozmiar - 1);
                city2 = rand() % (rozmiar - 1);
            }while(city1 == city2 || city1 == 0 || city2 == 0);

            int buff = population[i].path[city1];
            population[i].path[city1] = population[i].path[city2];
            population[i].path[city2] = buff;
        }
    }
}

void Algorithm::Selection(int &rozmiar, vector<Chromosome> &population, Chromosome best, vector<vector<int>> &m)
{
    if(population.size() < selection_min)
        return;

    double crit = 0;

    for(int i = 0; i < size_of_pop; i++)
    {
        crit+=population[i].fitness;
    }

    crit = crit / double(size_of_pop);

    for(int i = 0; i < size_of_pop; i++)
    {
        if(population[i].fitness < crit)
        {
            population.erase(population.begin() + i);
            size_of_pop = population.size();
            if(population.size() < initial_size)
                break;
        }
    }
}

bool Algorithm::CkeckTime(long long int start, long long int frequency)
{
    long long  int elapsed = read_QPC() - start;
    if(float(elapsed / frequency) >= stop)
    {
        return true;
    }
    return false;
}

void Algorithm::TSP(vector<vector<int>> matrix)
{
    srand(time(NULL));
    /* cities -> posortowana lista miast (kolejnosc wg indeksow w macierzy) */
    vector<int> cities;
    int rozmiar = matrix.size();

    for(int i=0; i<rozmiar; i++)
        cities.push_back(i);

    int best_cost;

    vector<Chromosome> population;
    Create_population(matrix, cities, rozmiar, population);

    // Zmienne do pomiaru czasu
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

    //kryterium stopu (czas w sekundach)
    // jezeli kryterium nie zostalo wprowadzone w menu, to domyslna wartoscia wynosi 10 sekund

    Chromosome best_chromosome = *new Chromosome(cities);
    start = read_QPC();
    while(true)
    {
        for(int i = 0; i < size_of_pop; i++)
        {
            population[i].calculateFitness(matrix);
        }

        CrossOver(rozmiar, population);
        Mutation(rozmiar, population);
        Selection(rozmiar, population, best_chromosome, matrix);
        size_of_pop = population.size();

    /*  for(int i = 0; i < size_of_pop; i++)
        {
            population[i].calculateFitness(matrix);
        }*/
        best_chromosome = M_val(matrix, population);
        best_cost = best_chromosome.calculateFitness(matrix);

        // Porownanie czasu wykonania z kryterium stopu
        elapsed = read_QPC() - start;
        if(float(elapsed/frequency) >= stop)
            break;
    }

    cout<<"Sciezka: \n";
    for(int city : best_chromosome.path)
        cout<<" -> "<<city<<" ";

    cout<<endl<<"Koszt: "<<best_cost<<endl;
}