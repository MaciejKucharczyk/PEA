#include "Matrix.h"
#include "Algorithm.h"
#include <iostream>
#include <windows.h>
#include <thread>

using namespace std;

/*//-------------------------------------------------------------------------
long long int read_QPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}

// Zmienne do pomiaru czasu
long long int frequency, start, elapsed;
//-------------------------------------------------------------------------

static bool s_Finished = false;*/

void print_options()
{
    cout<<"===== PROBLEM KOMIWOJAZERA =====\n";
    cout<<" ----- Wybierz czynnosc -----\n";
    cout<<"1. Wczytaj dane\n";
    cout<<"2. Kryterium stopu (default: 10)\n";
    cout<<"3. Wielkosc populacji poczatkowej (default: 10)\n";
    cout<<"4. Wspolczynnik mutacji (default: 0.01)\n";
    cout<<"5. Wyswietl macierz\n";
    cout<<"6. Uruchom algorytm\n";
    cout<<"7. Test\n";
    cout<<"0. Exit\n";
}

void choose_option(Matrix macierz)
{
    int opt=0;

   Algorithm *alg = new Algorithm();

    do
    {
        string NAME;
        print_options();
        cin>>opt;
        switch(opt)
        {
            case 1: // wczytywanie danych z pliku
                cout<<"Podaj nazwe pliku:\n";
                cin>>NAME;
                macierz.read_from_file(NAME);
                break;

            case 2: // kryterium stopu
                cout << "Wprowadz kryterium stopu: [s]\n";
                cin >> alg->stop;
                break;

            case 3: // wielkosc populacji poczatkowej
                cout << "Podaj wielkosc populacji poczatkowej: "<< endl;
                cin >> alg->initial_size;
                alg->size_of_pop = alg->initial_size;
                break;

            case 4: // ustawienie wspolczynnika mutacji
                cout << "Podaj wspolczynnik mutacji: [0 - 1]"<< endl;
                cin >> alg->mutation_rate;
                break;

            case 5: // wyswietlanie macierzy
                cout << endl << "Macierz:" << endl;
                macierz.print_matrix();
                break;

            case 6: // Uruchom algorytm
               alg->TSP(macierz.return_matrix());
                break;


            case 7: //test
                cout << "Na razie pusto..."<< endl;
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

