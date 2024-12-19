#include <iostream>

#include "Mapa/Mapa.h"

using namespace std;

int main() {
    Mapa m = Mapa::readFile("configs.txt");
    cout << m;
    Caravana* c = Caravana::find(&m, '2');
    string n = "C";
    c->move(&m, n);
    cout << m;
    return 0;
}
