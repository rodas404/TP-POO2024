#include <iostream>
#include "Mapa/Mapa.h"

using namespace std;

int main() {
    Mapa m = Mapa::readFile("configs.txt");
    m.move(3,3,2,10);
    cout << m;
    return 0;
}
