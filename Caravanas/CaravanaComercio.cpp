//
// Created by rodrigo on 18-12-2024.
//
#include <iostream>
#include "CaravanaComercio.h"
#include "../Mapa/Mapa.h"
using namespace std;

CaravanaComercio::CaravanaComercio(char id_, int m): Caravana(id_, 20, 40, 200, false, m) {

}

CaravanaComercio *CaravanaComercio::duplica() const {
    return new CaravanaComercio(*this);
}


void CaravanaComercio::move(Mapa *mapa) {
    int x, y;
    for (x=0; x < mapa->getRows(); ++x) {
        for (y=0; y < mapa->getCols(); ++y) {
            if (mapa->getMapa()[x][y].getTipo() == Localizacoes::Caravana) {
                if (mapa->getMapa()[x][y].getCaravana() == this) {
                    cout << "encontrei me\n";
                    break;
                }
            }
        }
    }



}
