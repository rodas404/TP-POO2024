//
// Created by rodrigo on 18-12-2024.
//

#include "CaixaPandora.h"
#include "../Localizações/Caravana.h"
#include <sstream>
using namespace std;

CaixaPandora::CaixaPandora(const int lifetime): Item(lifetime){}

void CaixaPandora::action(Caravana *car) {
    int tripulacao = car->getTripulantes();
    tripulacao = static_cast<int>(tripulacao * 0.8);
    car->setTripulantes(tripulacao);
}

std::string CaixaPandora::getDescricao() const {
    ostringstream oss;
    oss << "Item 'Caixa de Pandora' n " << this->getId() << " com "
        << this->getTimeLeft() << " segundos restantes."
            << "\nEste item mata 20% da tripulacao da caravana." << endl;
    return oss.str();
}






