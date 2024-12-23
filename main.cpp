#include <iostream>
#include "Mapa/Mapa.h"

using namespace std;

int main() {
    Mapa m = Mapa::readFile("configs.txt");
    cout << m;
    Caravana* c = Caravana::find(&m, '1');
    string n = "C";




    return 0;
}
