//
// Created by rodrigo on 18-12-2024.
//

#include "Jaula.h"
#include <sstream>
#include "../Localizações/Caravana.h"
using namespace std;

Jaula::Jaula(const int lifetime): Item(lifetime){}


void Jaula::action(Caravana *car) {
    car->setTripulantes(car->getMaxTrip());
}

std::string Jaula::getDescricao() const {
    ostringstream oss;
    oss << "Item 'Jaula' n " << this->getId() << " com "
        << this->getTimeLeft() << " segundos restantes."
            << "\nEste item liberta prisioneiros de guerra que se juntam a tripulacao." << endl;
    return oss.str();
}

