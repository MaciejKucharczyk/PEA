#include <iostream>
#include "matrix.h"
#include "Brute_force.h"
#include "Test.h"
#include "Branch_Bound.h"
#include <windows.h>

using namespace std;

//#define NAME    "tsp_17.txt"
//#define SIZE    17

int size_of_m=0;
string filename;

//-------------------------------------------------------------------------
long long int read_QPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}
//-------------------------------------------------------------------------


void print_options()
{
    cout<<"=== PROBLEM KOMIWOJAZERA ===\n";
    cout<<"Wybierz algorytm\n";
    cout<<"1. Wczytaj dane\n";
    cout<<"2. Przeglad zupelny\n";
    cout<<"3. B & B\n";
    cout<<"4. Wyswietl macierz\n";
    cout<<"5. Test\n";
    cout<<"0. Exit\n";
}

void choose_option(Matrix macierz)
{
    long long int frequency, start, elapsed;
    QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
    Branch_Bound bb;
    int opt=0;
    do
    {
        print_options();
        cin>>opt;
        switch(opt)
        {
            case 1: // wczytywanie danych z pliku
                cout<<"Wprowadz nazwe pliku: \n";
                cin>>filename;
                macierz.read_from_file(filename);
                break;

            case 2: // przeglad zupelny BF
                start = read_QPC();
                Brute_force::shortest_path(macierz.return_matrix());
                elapsed = read_QPC() - start;
                cout<<"czas: "<<  (1000000.0 * elapsed) / frequency <<" [us]"<<endl;
                break;

            case 3:
                // B & B
                bb.setSize(size_of_m);
                start = read_QPC();
                bb.TSP(macierz.return_matrix());
                elapsed = read_QPC() - start;
                cout<<"czas: "<<  (1000000.0 * elapsed) / frequency <<" [us]"<<endl;
                break;

            case 4: //wyswietlanie macierzy
                macierz.print_matrix();
                break;

            case 5: //test
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
    Matrix macierz;
    choose_option(macierz);
}
