//
// Created by Maciej on 05.11.2022.
//

#include "Test.h"
#include "Brute_force.h"
#include "Branch_Bound.h"
#include <iostream>
#include <chrono>
#include <fstream>

#define filename    "Brute.csv"

void Test::test_BF()
{
    Brute_force b;
    vector<vector<int>> test_m;

    fstream file;
    file.open(filename, ios::out | ios::app);
    file << endl << "BRUTE FORCE "<< endl;

    for(int i=0; i<7; i++)
    {
        float avg=0;
        int size = i+4; // zaczynamy od rozmiaru 3, konczymy na 10
        file << endl << "ROZMIAR "<<i+4<< endl;
        for(int j=0; j<100; j++)
        {
            // generowanie losowej macierzy
            test_m.resize(size);
            int val=0;
            for(int k=0; k<size; k++)
            {
                test_m[k].resize(size);
                for(int l=0; l<size; l++)
                {
                    if(k==l)
                        test_m[k][l]=0;
                    else
                    {
                        val=rand()%100;
                        test_m[k][l] = val;
                    }
                }
            }

            // czas start
            auto t1 = std::chrono::high_resolution_clock::now(); // czas start
            b.shortest_path(test_m, size);
            auto t2 = std::chrono::high_resolution_clock::now();
            //czas stop
            avg+= std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
            // TODO: zapis do CSV (fstream)
            cout<<"Rozmiar: "<<size<<"    sredni czas:"<<avg<<endl;
        }
        file << avg << endl;
    }
    file.close();
}

void Test::test_BB()
{
    //M_Generator m;
    vector<vector<int>> test_m;

    for(int i=0; i<7; i++)
    {
        float avg=0;
        int size = i+4; // zaczynamy od rozmiaru 4, konczymy na 11
        for(int j=0; j<100; j++)
        {
            // generowanie losowej macierzy
            test_m.resize(size);
            int val=0;
            for(int k=0; k<size; k++)
            {
                test_m[k].resize(size);
                for(int l=0; l<size; l++)
                {
                    if(k==l)
                        test_m[k][l]=0;
                    else
                    {
                        val=rand()%100;
                        test_m[k][l] = val;
                    }
                }
            }
            Branch_Bound bb(size);
            // czas start
            auto t1 = std::chrono::high_resolution_clock::now(); // czas start
            bb.TSP(test_m);
            //czas stop
            auto t2 = std::chrono::high_resolution_clock::now();
            // TODO: zapis do CSV (fstream)
            avg+=std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        }
        cout<<"Rozmiar: "<<size<<"    sredni czas:"<<avg<<endl;
    }
}

void Test::test_test() {

    int opt=0;
    do
    {
        cout<<"Wybierz test: \n";
        cout <<"1. Brute Force\n";
        cout<<"2. Branch & Bound\n";
        cout<<"0. Exit \n";

        cin>>opt;
        switch(opt)
        {
            case 1: // Brute Force
                test_BF();
                break;

            case 2: // Branch & Bound
                test_BB();
                break;

            default:
                cout<<"Wybierz opcje ponownie\n";
                break;
        }
    }
    while(opt!=0);
}
