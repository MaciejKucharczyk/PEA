#include <iostream>
#include "matrix.h"
#include "Tabu.h"

using namespace std;

void print_options()
{
    cout<<"=== PROBLEM KOMIWOJAZERA ===\n";
    cout<<"Wybierz algorytm\n";
    cout<<"1. Wczytaj dane\n";
    cout<<"2. Wprowadz kryterium stopu\n";
    cout<<"3. Wylacz / wlacz dysweryfikacje\n"; // to chyba opduscimy
    cout<<"4. Wybor sasiedztwa\n";
    cout<<"5. Uruchom algorytm\n";
    cout<<"6. Wyswietl macierz + Test\n";
    cout<<"0. Exit\n";
}

void choose_option(Matrix macierz)
{
    int opt=0;
    Tabu t;
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
               // Brute_force::shortest_path(macierz.return_matrix(), SIZE);
                break;

            case 3: // dysweryfikacja
               // bb.TSP(macierz.return_matrix());
                break;

            case 4: //wyswietlanie macierzy + test
                macierz.print_matrix();
                break;

            case 5: // uruchom algorytm
                t.TSP(macierz.return_matrix());
                //cout<<""<<endl;
                break;

            case 6: // wyswietl + test
                cout<<"Macierz:\n";
                macierz.print_matrix();
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
