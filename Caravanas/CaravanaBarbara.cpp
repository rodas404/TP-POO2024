//
// Created by rodrigo on 19-12-2024.
//

#include "CaravanaBarbara.h"
#include <random>
#include <sstream>
#include <iostream>
#include "../Mapa/Mapa.h"
using namespace std;

CaravanaBarbara::CaravanaBarbara(const int lifetime): Caravana('\0', 40, 0, 0, true, lifetime, 40, Tipos::Barbara, 1) {

}

CaravanaBarbara::CaravanaBarbara(const CaravanaBarbara &outro) = default;

CaravanaBarbara &CaravanaBarbara::operator=(const CaravanaBarbara &outro) {
    if (this == &outro)
        return *this;

    Caravana::operator=(outro);
    return *this;
}
CaravanaBarbara *CaravanaBarbara::duplica() const {
    return new CaravanaBarbara(*this);
}

std::string CaravanaBarbara::getInfo() const {
    ostringstream oss;
    oss << "Caravana Barbara '" << this->getId() << "'\n" << Caravana::getInfo();
    return oss.str();
}



int CaravanaBarbara::move(Mapa *mapa) {
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

    if (abs(targetRow - row) > 1) //verificar se esta a mover um espaço apenas
        targetRow = row + (targetRow > row ? 1 : -1);
    if (abs(targetCol - col) > 1)
        targetCol = col + (targetCol > col ? 1 : -1);

    // se nao encontrar caravana, ou a posicao escolhida for invalida, escolhe aleatoria
    if (!found || (mapa->getMapa()[targetRow][targetCol].getTipo() != Localizacoes::Deserto &&
                    mapa->getMapa()[targetRow][targetCol].getTipo() != Localizacoes::Cidade)) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 3);

        do {
            switch (dis(gen)) {
                case 0: targetCol = (col + 1) % mapa->getCols(); break; // dir
                case 1: targetCol = (col - 1 + mapa->getCols()) % mapa->getCols(); break; // esq
                case 2: targetRow = (row + 1) % mapa->getRows(); break; // baixo
                case 3: targetRow = (row - 1 + mapa->getRows()) % mapa->getRows(); break; // cima
            }
        } while (mapa->getMapa()[targetRow][targetCol].getTipo() != Localizacoes::Deserto &&
                 mapa->getMapa()[targetRow][targetCol].getTipo() != Localizacoes::Cidade);
    }

    int res = mapa->move(this, targetRow, targetCol);
    this->setDeathCount(this->getDeathCount() - 1);
    return res;
}

void CaravanaBarbara::consomeAgua() {

}

int CaravanaBarbara::lastMoves(Mapa *mapa) {
    return 0;
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
