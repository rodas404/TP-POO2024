//
// Created by rodrigo on 18-12-2024.
//

#include "CaixaPandora.h"
#include "../Localizações/Caravana.h"
using namespace std;

CaixaPandora::CaixaPandora()= default;

void CaixaPandora::action(Caravana *car) {
    int tripulacao = car->getTripulantes();
    tripulacao = static_cast<int>(tripulacao * 0.8);
    car->setTripulantes(tripulacao);
}






