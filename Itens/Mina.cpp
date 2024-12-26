//
// Created by rodrigo on 18-12-2024.
//

#include "Mina.h"
#include <sstream>
#include "../Localizações/Caravana.h"
using namespace std;

Mina::Mina() = default;


void Mina::action(Caravana *car) {
    car->setDeathCount(0);
}

std::string Mina::getDescricao() const {
    ostringstream oss;
    oss << "Item 'Mina' n " << this->getId() << " com "
        << this->getTimeLeft() << " segundos restantes."
            << "\nEste item destroi a caravana por completo." << endl;
    return oss.str();
}
