#include <iostream>
#include <windows.h>
#include "matrix.h"
#include "Tabu.h"
#include "Wyzarzanie.h"

using namespace std;

void print_options()
{
    cout<<"===== PROBLEM KOMIWOJAZERA =====\n";
    cout<<" = Wybierz czynnosc =\n";
    cout<<"1. Wczytaj dane\n";
    cout<<"2. Wprowadz kryterium stopu\n";
    cout<<"3. Wyswietlanie macierzy\n";
    cout<<"4. Uruchom algorytm\n";
    cout<<"0. Exit\n";
}

void choose_alg(Matrix macierz, Tabu t, Wyzarzanie w)
{
    int op = 0;
    do
    {
        cout<<"=== WYBIERZ ALGORYTM ==="<<endl;
        cout<<"1. Symulowane wyzarzanie"<<endl;
        cout<<"2. Tabu search"<<endl;
        cout<<"3. Wyjscie"<<endl;
        cin>>op;
        switch(op)
        {
            case 1: // SA
                w.TSP(macierz.return_matrix());
                break;
            case 2: // tabu search
                t.TSP(macierz.return_matrix());
                break;
            default:
                cout<<"Podano zly numer opcji"<<endl;
                break;
        }
    }
    while(op!=0);
}

void choose_option(Matrix macierz)
{
    int opt=0;
    Tabu t;
    Wyzarzanie w;
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
                cout<<"Wprowadz kryterium stopu: [s]\n";
                cin>>t.stop;
                break;

            case 3: // dysweryfikacja
                cout<<"Macierz:\n";
                macierz.print_matrix();
                break;

            case 4: //wyswietlanie macierzy
                choose_alg(macierz, t, w);
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
