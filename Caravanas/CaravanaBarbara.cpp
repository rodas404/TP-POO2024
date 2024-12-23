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
    auto[row, col] = this->getCoordenadas(mapa);
    int targetRow = row, targetCol = col;
    bool found = false;

    for (int i = -8; i <= 8; ++i) {
        for (int j = -8; j <= 8; ++j) {
            int newRow = (row + i + mapa->getRows()) % mapa->getRows();
            int newCol = (col + j + mapa->getCols()) % mapa->getCols();

            Caravana *caravana = mapa->getMapa()[newRow][newCol].getCaravana();
            if (caravana && caravana->getTipo() != Tipos::Barbara) {
                targetRow = newRow;
                targetCol = newCol;
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

    // Perform necessary checks
    mapa->move(this, targetRow, targetCol);
    this->setDeathCount(this->getDeathCount() - 1);
}

void CaravanaBarbara::consomeAgua() {

}

void CaravanaBarbara::lastMoves(Mapa *mapa) {

}


void CaravanaBarbara::efeitoTempestade() {
    int tripulacao = this->getTripulantes();
    int posTempestade = static_cast<int>(tripulacao * 0.9);
    this->setTripulantes(posTempestade);

    if (tripulacao == 0) {
        this->setDeathCount(0);
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    if (dis(gen) < 0.25)
        this->setDeathCount(0);
}
