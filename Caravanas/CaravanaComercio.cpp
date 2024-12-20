//
// Created brow rodrigo on 18-12-2024.
//
#include <iostream>
#include "CaravanaComercio.h"
#include "../Mapa/Mapa.h"
#include <string>
#include <sstream>
#include <random>
using namespace std;

CaravanaComercio::CaravanaComercio(char id_): Caravana(id_, 20, 40, 200, false, 5, 20, Tipos::Comercio) {

}

CaravanaComercio *CaravanaComercio::duplica() const {
    return new CaravanaComercio(*this);
}


void CaravanaComercio::move(Mapa *mapa,string &direction) {
    Caravana::move(mapa, direction);
    consomeAgua();
}


void CaravanaComercio::move(Mapa *mapa) {
    auto[col, row] = this->getCoordenadas(mapa);
    int targetCol = col, targetRow = row;
    bool flag = false;

    for (int i = -2; i<=2; ++i) {
        for (int j = -2; j<=2; ++j) {
            //jogar com os limites do mapa
            int newCol = (col + i + mapa->getCols()) % mapa->getCols();
            int newRow = (row + j + mapa->getRows()) % mapa->getRows();
            Caravana *caravana = mapa->getMapa()[newRow][newCol].getCaravana();
            if (caravana && caravana->getTipo() != Tipos::Barbara) {
                targetCol = newCol;
                targetRow = newRow;
                flag = true;
                break;
            }
        }
        if (flag) break;
    }

    flag = false;
    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            int newCol = (col + i + mapa->getCols()) % mapa->getCols();
            int newRow = (row + j + mapa->getRows()) % mapa->getRows();
            if (mapa->getMapa()[newRow][newCol].getItem()) {
                targetCol = newCol;
                targetRow = newRow;
                flag = true;
                break;
            }
        }
        if (flag) break;
    }

    //selecionar aleatoriamente
    if (targetCol == col && targetRow == row) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 3);

        while (true) {
            int direction = dis(gen);
            int newCol = col, newRow = row;
            switch (direction) {
                case 0: newCol = (col + 1 + mapa->getCols()) % mapa->getCols(); break; // direita
                case 1: newCol = (col - 1 + mapa->getCols()) % mapa->getCols(); break; // esquerda
                case 2: newRow = (row + 1 + mapa->getRows()) % mapa->getRows(); break; // baixo
                case 3: newRow = (row - 1 + mapa->getRows()) % mapa->getRows(); break; // cima
            }
            if (mapa->getMapa()[newRow][newCol].getTipo() == Localizacoes::Deserto ||
                mapa->getMapa()[newRow][newCol].getTipo() == Localizacoes::Cidade) {
                targetCol = newCol;
                targetRow = newRow;
                break;
                }
        }
    }

    consomeAgua();
    //as caravanas so podem andar uma casa, precisa de verificações para não andar mais que uma casa e essa casa só pode ser deserto ou cidade. o stor não é claro acerca se as caravanas tem o mesmo alcance de perceção para caravanas e itens
    mapa->move(this, targetCol, targetRow);
}


std::string CaravanaComercio::getInfo() const {
    ostringstream oss;
    oss << "Caravana Comercio '" << this->getId() <<"'\n" << Caravana::getInfo();
    return oss.str();
}

void CaravanaComercio::consomeAgua() {
    int tripulacao = this->getTripulantes();
    int maxTrip = this->getMaxTrip();
    int aguaConsumida = 0;

    if (tripulacao > 0) {
        if (tripulacao >= maxTrip / 2) {
            aguaConsumida = 2;
        } else
            aguaConsumida = 1;
    }
    this->setAgua(this->getAgua() - aguaConsumida);
}


void CaravanaComercio::lastMoves(Mapa *mapa) {
    auto [col, row] = this->getCoordenadas(mapa);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);

    while (true) {
        int direction = dis(gen);
        int newCol = col, newRow = row;
        switch (direction) {
            case 0: newCol = (col + 1 + mapa->getCols()) % mapa->getCols(); break; // right
            case 1: newCol = (col - 1 + mapa->getCols()) % mapa->getCols(); break; // left
            case 2: newRow = (row + 1 + mapa->getRows()) % mapa->getRows(); break; // down
            case 3: newRow = (row - 1 + mapa->getRows()) % mapa->getRows(); break; // up
        }
        if (mapa->getMapa()[newRow][newCol].getTipo() == Localizacoes::Deserto ||
            mapa->getMapa()[newRow][newCol].getTipo() == Localizacoes::Cidade) {
            mapa->move(this, newCol, newRow);
            break;
        }
    }
    this->setDeathCount(this->getDeathCount()-1);
}

