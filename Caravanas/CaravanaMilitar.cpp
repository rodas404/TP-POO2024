//
// Created by rodrigo on 18-12-2024.
//
#include <iostream>
#include <sstream>
#include <string>
#include "CaravanaMilitar.h"
#include "../Mapa/Mapa.h"
using namespace std;

CaravanaMilitar::CaravanaMilitar(char id_): Caravana(id_, 40, 5, 400, false, 7, 40, Tipos::Militar) {

}

CaravanaMilitar *CaravanaMilitar::duplica() const {
    return new CaravanaMilitar(*this);
}

void CaravanaMilitar::move(Mapa *mapa, string &direction) {
    Caravana::move(mapa, direction);
    consomeAgua();
}



void CaravanaMilitar::move(Mapa *mapa) {
    auto[col, row] = this->getCoordenadas(mapa);
    int targetCol = col, targetRow = row;
    bool found = false;

    for (int i = -6; i <= 6; ++i) {
        for (int j = -6; j <= 6; ++j) {
            int newCol = (col + i + mapa->getCols()) % mapa->getCols();
            int newRow = (row + j + mapa->getRows()) % mapa->getRows();

            Caravana *caravana = mapa->getMapa()[newRow][newCol].getCaravana();
            if (caravana && caravana->getTipo() == Tipos::Barbara) {
                targetCol = newCol;
                targetRow = newRow;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    if (targetRow != row && targetCol != col)
        consomeAgua();

    //fazer verificações
    mapa->move(this, targetCol, targetRow);
}

std::string CaravanaMilitar::getInfo() const {
    ostringstream oss;
    oss << "Caravana Militar '" << this->getId() << "'\n" << Caravana::getInfo();
    return oss.str();
}


void CaravanaMilitar::consomeAgua() {
    int tripulacao = this->getTripulantes();
    int maxTrip = this->getMaxTrip();
    int aguaConsumida;

    if (tripulacao >= maxTrip / 2)
        aguaConsumida = 3;
    else
        aguaConsumida = 1;

    this->setAgua(this->getAgua() - aguaConsumida);
}


void CaravanaMilitar::lastMoves(Mapa *mapa) {
    static std::string lastDirection = "right"; // Default initial direction

    auto [col, row] = this->getCoordenadas(mapa);
    int newCol = col, newRow = row;

    if (lastDirection == "right") {
        newCol = (col + 1 + mapa->getCols()) % mapa->getCols();
    } else if (lastDirection == "left") {
        newCol = (col - 1 + mapa->getCols()) % mapa->getCols();
    } else if (lastDirection == "down") {
        newRow = (row + 1 + mapa->getRows()) % mapa->getRows();
    } else if (lastDirection == "up") {
        newRow = (row - 1 + mapa->getRows()) % mapa->getRows();
    }

    if (mapa->getMapa()[newRow][newCol].getTipo() == Localizacoes::Deserto ||
        mapa->getMapa()[newRow][newCol].getTipo() == Localizacoes::Cidade) {
        mapa->move(this, newCol, newRow);
    }
    this->setDeathCount(this->getDeathCount()-1);
    // Update lastDirection if needed
    // lastDirection = "new_direction"; // Uncomment and set new direction if needed
}
