//
// Created by rodrigo on 19-12-2024.
//

#include "PacoteSuspenso.h"

#include "../Localizações/Caravana.h"

PacoteSuspenso::PacoteSuspenso() = default;

PacoteSuspenso *PacoteSuspenso::duplica() const {
    return new PacoteSuspenso(*this);
}

void PacoteSuspenso::action(Caravana *car) {
    car->setMercadorias(car->getMaxMerc());
}


