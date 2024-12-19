//
// Created by rodrigo on 18-12-2024.
//

#include "Mina.h"

Mina::Mina() = default;

Mina *Mina::duplica() const {
    return new Mina(*this);
}

void Mina::action(Caravana *car) {

}

