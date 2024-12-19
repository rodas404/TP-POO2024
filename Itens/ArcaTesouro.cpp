//
// Created by rodrigo on 18-12-2024.
//

#include "ArcaTesouro.h"

#include "../Localizações/Caravana.h"

ArcaTesouro::ArcaTesouro() = default;


ArcaTesouro *ArcaTesouro::duplica() const {
    return new ArcaTesouro(*this);
}

void ArcaTesouro::action(Caravana *car) {
    float moedas = car->getMoedas();
    moedas *= 1.1;
    car->setMoedas(moedas);
}

