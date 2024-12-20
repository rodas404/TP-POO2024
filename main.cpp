#include <iostream>

#include "Mapa/Mapa.h"

using namespace std;

int main() {
    Mapa m = Mapa::readFile("configs.txt");
    cout << m;
    Caravana* c = Caravana::find(&m, '1');
    string n = "CD";
    m.move(c, 5, 5);
    cout << m;
    m.move(c,2,2);
    cout << m;


    return 0;
}
