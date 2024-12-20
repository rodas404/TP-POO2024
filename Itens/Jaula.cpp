//
// Created by rodrigo on 18-12-2024.
//

#include "Jaula.h"

#include "../Localizações/Caravana.h"

Jaula::Jaula() = default;


void Jaula::action(Caravana *car) {
    car->setTripulantes(car->getMaxTrip());
}


