//
// Created by rodrigo on 19-12-2024.
//

#include "CaravanaBarbara.h"
#include <random>
#include "../Mapa/Mapa.h"

CaravanaBarbara::CaravanaBarbara(const int lifetime): Caravana('!', 40, 0, 0, true, lifetime, 50, Tipos::Barbara) {

}


CaravanaBarbara *CaravanaBarbara::duplica() const {
    return new CaravanaBarbara(*this);
}


void CaravanaBarbara::move(Mapa *mapa) {
    auto[col, row] = this->getCoordenadas(mapa);
    int targetCol = col, targetRow = row;
    bool found = false;

    for (int i = -8; i <= 8; ++i) {
        for (int j = -8; j <= 8; ++j) {
            if (i == 0 && j == 0) continue; // Skip the current position
            int newCol = (col + i + mapa->getCols()) % mapa->getCols();
            int newRow = (row + j + mapa->getRows()) % mapa->getRows();

            Caravana *caravana = mapa->getMapa()[newRow][newCol].getCaravana();
            if (caravana && caravana->getTipo() != Tipos::Barbara) {
                targetCol = newCol;
                targetRow = newRow;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    // If a non-barbarian caravan is found, move one position towards it
    if (!found) {

        // Move randomly if no non-barbarian caravan is found
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 3);

        switch (dis(gen)) {
            case 0: targetCol = (col + 1) % mapa->getCols(); break; // Right
            case 1: targetCol = (col - 1 + mapa->getCols()) % mapa->getCols(); break; // Left
            case 2: targetRow = (row + 1) % mapa->getRows(); break; // Down
            case 3: targetRow = (row - 1 + mapa->getRows()) % mapa->getRows(); break; // Up
        }
    }

    //fazer verificações necessarias
    mapa->move(this, targetCol, targetRow);
    this->setDeathCount(this->getDeathCount()-1);
}

void CaravanaBarbara::consomeAgua() {

}

void CaravanaBarbara::lastMoves(Mapa *mapa) {

}