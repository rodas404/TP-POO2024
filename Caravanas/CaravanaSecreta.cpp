//
// Created by rodrigo on 28-12-2024.
//
#include <iostream>
#include <sstream>
#include <string>
#include "CaravanaSecreta.h"
#include "../Mapa/Mapa.h"
#include <random>
using namespace std;


CaravanaSecreta::CaravanaSecreta(const char id_): Caravana(id_, 30, 0, 350, false, 3, 40, Tipos::Secreta, 1) {

}
CaravanaSecreta::CaravanaSecreta(const CaravanaSecreta &outro) : Caravana(outro) {
}

CaravanaSecreta &CaravanaSecreta::operator=(const CaravanaSecreta &outro) {
    if (this == &outro)
        return *this;

    Caravana::operator=(outro);
    return *this;
}

CaravanaSecreta *CaravanaSecreta::duplica() const {
    return new CaravanaSecreta(*this);
}

void CaravanaSecreta::consomeAgua() {
    int tripulacao = this->getTripulantes();
    int maxTrip = this->getMaxTrip();
    int aguaConsumida;

    if (this->getAgua() == 0) {
        this->setTripulantes(tripulacao-1);
        return;
    }

    if (tripulacao >= maxTrip / 2)
        aguaConsumida = 3;
    else
        aguaConsumida = 5;

    this->setAgua(this->getAgua() - aguaConsumida);
}

std::string CaravanaSecreta::getInfo() const {
    ostringstream oss;
    oss << "Caravana Secreta '" << this->getId() << "'\n" << Caravana::getInfo();
    return oss.str();
}

void CaravanaSecreta::efeitoTempestade() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    if (dis(gen) < 0.4) {
        int tripulacao = this->getTripulantes();
        int posTempestade = static_cast<int>(tripulacao * 0.75);
        this->setTripulantes(posTempestade);
    }
}

int CaravanaSecreta::move(Mapa *mapa, std::string &direction) {
    int res = Caravana::move(mapa, direction);
    if (res == -1)
        return -1;
    consomeAgua();
    return res;
}

int CaravanaSecreta::move(Mapa *mapa) {
    auto[row, col] = this->getCoordenadas(mapa);
    int targetRow = row, targetCol = col;


    bool found = false;

    // procurar cidade em 4 celulas de distancia
    for (int i = -4; i <= 4 && !found; ++i) {
        for (int j = -4; j <= 4 && !found; ++j) {
            int newRow = (row + i + mapa->getRows()) % mapa->getRows();
            int newCol = (col + j + mapa->getCols()) % mapa->getCols();
            if (mapa->getMapa()[newRow][newCol].getTipo() == Localizacoes::Cidade) {
                targetRow = newRow;
                targetCol = newCol;
                found = true;
            }
        }
    }

    if (abs(targetRow - row) > 1) //verificar se está a mover um espaço apenas
        targetRow = row + (targetRow > row ? 1 : -1);
    if (abs(targetCol - col) > 1)
        targetCol = col + (targetCol > col ? 1 : -1);

    // se nenhuma cidade for encontrada, ou a celula escolhida for invalida, escolher posição aleatória válida
    if (!found || (mapa->getMapa()[targetRow][targetCol].getTipo() != Localizacoes::Deserto &&
                    mapa->getMapa()[targetRow][targetCol].getTipo() != Localizacoes::Cidade)) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 3);
        do {
            switch (dis(gen)) {
                case 0: targetCol = (col + 1) % mapa->getCols(); break; // Right
                case 1: targetCol = (col - 1 + mapa->getCols()) % mapa->getCols(); break; // Left
                case 2: targetRow = (row + 1) % mapa->getRows(); break; // Down
                case 3: targetRow = (row - 1 + mapa->getRows()) % mapa->getRows(); break; // Up
            }
        } while (mapa->getMapa()[targetRow][targetCol].getTipo() != Localizacoes::Deserto && mapa->getMapa()[targetRow][targetCol].getTipo() != Localizacoes::Cidade);
    }

    consomeAgua();
    int res = mapa->move(this, targetRow, targetCol);
    return res;
}

int CaravanaSecreta::lastMoves(Mapa *mapa) {
    setComportamento(true);
    this->setDeathCount(this->getDeathCount() - 1);
    return 0;
}

