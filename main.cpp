#include <iostream>
#include "Mapa/Mapa.h"

using namespace std;

int main() {
    Mapa m = Mapa::readFile("configs.txt");
    cout << m;
    return 0;
}
