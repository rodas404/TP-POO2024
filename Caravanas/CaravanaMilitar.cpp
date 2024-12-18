//
// Created by rodrigo on 18-12-2024.
//
#include <iostream>
#include "CaravanaMilitar.h"
using namespace std;

CaravanaMilitar::CaravanaMilitar(char id_, int m): Caravana(id_, 40, 5, 400, false, m), maxTripulantes(40) {

}

CaravanaMilitar *CaravanaMilitar::duplica() const {
    return new CaravanaMilitar(*this);
}

void CaravanaMilitar::move(Mapa *mapa) {
    cout << "fodase";
}
