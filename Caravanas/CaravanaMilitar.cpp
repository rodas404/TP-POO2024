//
// Created by rodrigo on 18-12-2024.
//
#include <iostream>
#include <sstream>
#include <string>
#include "CaravanaMilitar.h"
#include "../Mapa/Mapa.h"
#include <random>
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
    auto[row, col] = this->getCoordenadas(mapa);
    int targetRow = row, targetCol = col;
    bool found = false;

    for (int i = -6; i <= 6; ++i) {
        for (int j = -6; j <= 6; ++j) {
            int newRow = (row + i + mapa->getRows()) % mapa->getRows();
            int newCol = (col + j + mapa->getCols()) % mapa->getCols();

            Caravana *caravana = mapa->getMapa()[newRow][newCol].getCaravana();
            if (caravana && caravana->getTipo() == Tipos::Barbara) {
                targetRow = newRow;
                targetCol = newCol;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    if (targetRow != row || targetCol != col)
        consomeAgua();

    mapa->move(this, targetRow, targetCol);
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

    auto[row, col] = this->getCoordenadas(mapa);
    int newRow = row, newCol = col;

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
            mapa->move(this, newRow, newCol);
        }

    //incompleto e sem verificações
    this->setDeathCount(this->getDeathCount() - 1);
}

void CaravanaMilitar::efeitoTempestade() {
    int tripulacao = this->getTripulantes();
    int posTempestade = static_cast<int>(tripulacao * 0.9);
    this->setTripulantes(posTempestade);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    if (dis(gen) < 0.33)
        this->setDeathCount(0);

}
