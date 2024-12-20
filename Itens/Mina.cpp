//
// Created by rodrigo on 18-12-2024.
//

#include "Mina.h"

#include "../Localizações/Caravana.h"

Mina::Mina() = default;


void Mina::action(Caravana *car) {
    car->setDeathCount(0);
}

