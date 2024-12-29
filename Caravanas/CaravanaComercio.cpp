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

CaravanaComercio::CaravanaComercio(char id_): Caravana(id_, 20, 40, 200, false, 5, 20, Tipos::Comercio, 2) {

}

CaravanaComercio *CaravanaComercio::duplica() const {
    return new CaravanaComercio(*this);
}


void CaravanaComercio::move(Mapa *mapa,string &direction) {
    Caravana::move(mapa, direction);
    consomeAgua();
}

void CaravanaComercio::move(Mapa *mapa) {
    auto[row, col] = this->getCoordenadas(mapa);
    int targetRow = row, targetCol = col;
    bool flag = false;

    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            int newRow = (row + i + mapa->getRows()) % mapa->getRows();
            int newCol = (col + j + mapa->getCols()) % mapa->getCols();
            if (mapa->getMapa()[newRow][newCol].getItem()) {
                targetRow = newRow;
                targetCol = newCol;
                flag = true;
                break;
            }
        }
        if (flag) break;
    }

    if (!flag) {
        for (int i = -2; i <= 2; ++i) {
            for (int j = -2; j <= 2; ++j) {
                int newRow = (row + i + mapa->getRows()) % mapa->getRows();
                int newCol = (col + j + mapa->getCols()) % mapa->getCols();
                Caravana *caravana = mapa->getMapa()[newRow][newCol].getCaravana();
                if (caravana && caravana->getTipo() != Tipos::Barbara) {
                    targetRow = newRow;
                    targetCol = newCol;
                    flag = true;
                    break;
                }
            }
            if (flag) break;
        }
    }


    if (abs(targetRow - row) > 1) //verificar se esta a mover um espaço apenas
        targetRow = row + (targetRow > row ? 1 : -1);
    if (abs(targetCol - col) > 1)
        targetCol = col + (targetCol > col ? 1 : -1);


    // verifica se a celula escolhida e valida
    if (mapa->getMapa()[targetRow][targetCol].getTipo() != Localizacoes::Deserto &&
        mapa->getMapa()[targetRow][targetCol].getTipo() != Localizacoes::Cidade) {
        // se nao for, escolhe uma outra
        flag = false;
        for (int i = -1; i <= 1 && !flag; ++i) {
            for (int j = -1; j <= 1 && !flag; ++j) {
                int newRow = (row + i + mapa->getRows()) % mapa->getRows();
                int newCol = (col + j + mapa->getCols()) % mapa->getCols();
                if (mapa->getMapa()[newRow][newCol].getTipo() == Localizacoes::Deserto ||
                    mapa->getMapa()[newRow][newCol].getTipo() == Localizacoes::Cidade) {
                    targetRow = newRow;
                    targetCol = newCol;
                    flag = true;
                    }
            }
        }
        if (!flag) {
            targetRow = row;
            targetCol = col;
            }
        }

    consomeAgua();
    mapa->move(this, targetRow, targetCol);
}


std::string CaravanaComercio::getInfo() const {
    ostringstream oss;
    oss << "Caravana Comercio '" << this->getId() <<"'\n" << Caravana::getInfo();
    return oss.str();
}

void CaravanaComercio::consomeAgua() {
    int tripulacao = this->getTripulantes();
    int maxTrip = this->getMaxTrip();

    if (this->getAgua() == 0) {
        this->setTripulantes(tripulacao-1);
        return;
    }

    if (tripulacao > 0) {
        int aguaConsumida = 0;
        if (tripulacao >= maxTrip / 2)
            aguaConsumida = 2;
        else
            aguaConsumida = 1;
        this->setAgua(this->getAgua() - aguaConsumida);
    }


}


void CaravanaComercio::lastMoves(Mapa *mapa) {
    auto[row, col] = this->getCoordenadas(mapa);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);

    while (true) {
        int direction = dis(gen);
        int newRow = row, newCol = col;
        switch (direction) {
            case 0: newCol = (col + 1 + mapa->getCols()) % mapa->getCols(); break;
            case 1: newCol = (col - 1 + mapa->getCols()) % mapa->getCols(); break;
            case 2: newRow = (row + 1 + mapa->getRows()) % mapa->getRows(); break;
            case 3: newRow = (row - 1 + mapa->getRows()) % mapa->getRows(); break;
        }
        if (mapa->getMapa()[newRow][newCol].getTipo() == Localizacoes::Deserto ||
            mapa->getMapa()[newRow][newCol].getTipo() == Localizacoes::Cidade) {
                mapa->move(this, newRow, newCol);
                break;
            }
    }
    this->setDeathCount(this->getDeathCount() - 1);
}

void CaravanaComercio::efeitoTempestade() {
    float carrega = this->getMercadorias() / this->getMaxMerc();
    float probabilidade = (carrega > 0.5) ? 0.5 : 0.25;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    if (dis(gen) < probabilidade)
        this->setDeathCount(0);
    else {
        const float novoPeso = this->getMercadorias() * 0.75f;
        this->setMercadorias(novoPeso);
    }
}


