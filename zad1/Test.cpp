//
// Created by Maciej on 05.11.2022.
//

#include "Test.h"
#include "M_Generator.h"
#include "Brute_force.h"
#include <iostream>
#include <fstream>

void Test::test_BF()
{
    M_Generator m;
    Brute_force b;
    vector<vector<int>> test_m;

    for(int i=0; i<7; i++)
    {
        int size = i+3; // zaczynamy od rozmiaru 3, konczymy na 10
        for(int j=0; j<100; j++)
        {
            test_m = m.generate_matrix(size);
            // TODO: czas (chrono) lub coś innego
            // czas start
            //
            b.shortest_path(test_m, size);
            //czas stop
            // TODO: zapis do CSV czy cos (fstream)
        }
    }


}

void Test::test_BB() {

}

void Test::test_DP() {

}

void Test::test_test() {
    cout<<"Wybierz test: \n";
    cout <<"1. BF\n";
    cout<<"2. BB\n";
    cout<<"3. DP \n";
    cout<<"0. Exit \n";

    int opt=0;
    do
    {
        cin>>opt;
        switch(opt)
        {
            case 1: // Brute Force
                test_BF();
                break;

            case 2: // Branch & Bound
                test_BB();
                break;

            case 3:
                // Dynamic
                test_DP();
                break;

            default:
                cout<<"Wybierz opcje ponownie\n";
                break;
        }
    }
    while(opt!=0);
}
