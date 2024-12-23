//
// Created by rodrigo on 18-12-2024.
//

#include "ArcaTesouro.h"

#include "../Localizações/Caravana.h"

ArcaTesouro::ArcaTesouro() = default;


void ArcaTesouro::action(Caravana *car) {
    float moedas = static_cast<float>(Caravana::getMoedas() * 1.1);
    Caravana::setMoedas(moedas);
}

