#include <iostream>
#include "matrix.h"
#include "Brute_force.h"
#include "Test.h"
//#include "Branch_Bound.h"

using namespace std;

#define NAME    "tsp_17.txt"
#define SIZE    17

//Brute_force b;

void print_options()
{
    cout<<"=== PROBLEM KOMIWOJAZERA ===\n";
    cout<<"Wybierz algorytm\n";
    cout<<"1. Wczytaj dane\n";
    cout<<"2. Przeglad zupelny\n";
    cout<<"3. B & B\n";
    cout<<"4. DP\n";
    cout<<"5. Wyswietl macierz\n";
    cout<<"6. Test\n";
    cout<<"0. Exit\n";
}

void choose_option(Matrix macierz)
{
    int opt=0;
    do
    {
        print_options();
        cin>>opt;
        switch(opt)
        {
            case 1: // wczytywanie danych z pliku
                macierz.read_from_file(NAME);
                break;

            case 2: // przeglad zupelny BF
                Brute_force::shortest_path(macierz.return_matrix(), SIZE);
                break;

            case 3:
                // B&B
               // Branch_Bound::branch_bound(macierz.return_matrix(), SIZE);
                break;

            case 4: //dynamiczne
                cout<<"gowno"<<endl;
                break;

            case 5: //wyswietlanie macierzy
                macierz.print_matrix();
                break;

            case 6: //test
                Test t;
                t.test_test();
                cout<<"Test zakończony"<<endl;
                break;

            default:
                cout<<"Wybierz opcje ponownie\n";
                break;
        }
    }
    while(opt!=0);
}

int main()
{
    Matrix macierz(SIZE);
    choose_option(macierz);
}
