//
// Created by rodrigo on 19-12-2024.
//

#include "PacoteSuspenso.h"
#include <sstream>
#include "../Localizacoes/Caravana.h"
using namespace std;

PacoteSuspenso::PacoteSuspenso(const int lifetime): Item(lifetime){}


void PacoteSuspenso::action(Caravana *car) {
    car->setMercadorias(car->getMaxMerc());
}

std::string PacoteSuspenso::getDescricao() const {
    ostringstream oss;
    oss << "Item 'Pacote Suspenso' n " << this->getId() << " com "
        << this->getTimeLeft() << " segundos restantes."
            << "\nEste item caido do ceu tem mercadorias preciosas que enchem a capacidade da caravana." << endl;
    return oss.str();
}

