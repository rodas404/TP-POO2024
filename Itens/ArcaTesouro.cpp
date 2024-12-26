//
// Created by rodrigo on 18-12-2024.
//

#include "ArcaTesouro.h"
#include <sstream>
#include <string>
#include "../Localizações/Caravana.h"
using namespace std;

ArcaTesouro::ArcaTesouro() = default;


void ArcaTesouro::action(Caravana *car) {
    float moedas = static_cast<float>(Caravana::getMoedas() * 1.1);
    Caravana::setMoedas(moedas);
}


std::string ArcaTesouro::getDescricao() const {
    ostringstream oss;
    oss << "Item 'Arca do Tesouro' n " << this->getId() << " com "
        << this->getTimeLeft() << " segundos restantes."
            << "\nEste item acrescenta 10% as moedas do utilizador." << endl;
    return oss.str();
}
