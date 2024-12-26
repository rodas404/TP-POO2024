#include <iostream>
#include "Mapa/Mapa.h"
#include "Simulador/Simulador.h"

using namespace std;

int main() {
    /*Mapa m = Mapa::readFile("configs.txt");
    cout << m;

    string n = "C";
    m.spawnItem();
    m.move(c, 1,2);
    cout << m;*/
    Simulador sim = Simulador::readFile("configs.txt");
    cout << *sim.getMapa();


    return 0;
}
