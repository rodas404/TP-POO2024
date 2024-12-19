//
// Created brow rodrigo on 18-12-2024.
//
#include <iostream>
#include "CaravanaComercio.h"
#include "../Mapa/Mapa.h"
#include <string>
#include <sstream>
using namespace std;

CaravanaComercio::CaravanaComercio(char id_, int m): Caravana(id_, 20, 40, 200, false, m, 5) {

}

CaravanaComercio *CaravanaComercio::duplica() const {
    return new CaravanaComercio(*this);
}


void CaravanaComercio::move(Mapa *mapa,string &direction) {
    Caravana::move(mapa, direction);

}


std::string CaravanaComercio::getInfo() const {
    ostringstream oss;
    oss << "Caravana Comercio '" << this->getId() <<"'\n" << Caravana::getInfo();
    return oss.str();
}
