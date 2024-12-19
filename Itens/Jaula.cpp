//
// Created by rodrigo on 18-12-2024.
//

#include "Jaula.h"

#include "../Localizações/Caravana.h"

Jaula::Jaula() = default;

Jaula *Jaula::duplica() const {
    return new Jaula (*this);
}

void Jaula::action(Caravana *car) {
    int tripulacao = car->getTripulantes();


    car->setTripulantes(tripulacao);
}


