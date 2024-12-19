//
// Created by rodrigo on 18-12-2024.
//
#include <iostream>
#include <sstream>
#include <string>
#include "CaravanaMilitar.h"
using namespace std;

CaravanaMilitar::CaravanaMilitar(char id_, int m): Caravana(id_, 40, 5, 400, false, m, 7), maxTripulantes(40) {

}

CaravanaMilitar *CaravanaMilitar::duplica() const {
    return new CaravanaMilitar(*this);
}

void CaravanaMilitar::move(Mapa *mapa, string &direction) {
    cout << "fodase";
}

std::string CaravanaMilitar::getInfo() const {
    ostringstream oss;
    oss << "Caravana Militar '" << this->getId() << '\n' << Caravana::getInfo();
    return oss.str();
}
