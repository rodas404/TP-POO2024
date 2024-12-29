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

CaravanaMilitar::CaravanaMilitar(const char id_): Caravana(id_, 40, 5, 400, false, 7, 40, Tipos::Militar, 3), lastDirection("null") {

}

CaravanaMilitar *CaravanaMilitar::duplica() const {
    return new CaravanaMilitar(*this);
}
CaravanaMilitar::CaravanaMilitar(const CaravanaMilitar &outro) : Caravana(outro), lastDirection(outro.lastDirection) {
}

CaravanaMilitar &CaravanaMilitar::operator=(const CaravanaMilitar &outro) {
    if (this == &outro)
        return *this;

    Caravana::operator=(outro);
    lastDirection = outro.lastDirection;
    return *this;
}

int CaravanaMilitar::move(Mapa *mapa, string &direction) {
    int res = Caravana::move(mapa, direction);
    if (res == -1)
        return -1;
    setLastDirection(direction);
    consomeAgua();
    return res;
}



int CaravanaMilitar::move(Mapa *mapa) {
    auto[row, col] = this->getCoordenadas(mapa);
    if (row == -1 && col == -1)
        return -1;

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

    if (abs(targetRow - row) > 1) //verificar se esta a mover um espaço apenas
        targetRow = row + (targetRow > row ? 1 : -1);
    if (abs(targetCol - col) > 1)
        targetCol = col + (targetCol > col ? 1 : -1);

    // verifica se a celula escolhida e valida
    if (mapa->getMapa()[targetRow][targetCol].getTipo() != Localizacoes::Deserto &&
        mapa->getMapa()[targetRow][targetCol].getTipo() != Localizacoes::Cidade) {
        // se nao for, escolhe uma outra
        found = false;
        for (int i = -1; i <= 1 && !found; ++i) {
            for (int j = -1; j <= 1 && !found; ++j) {
                int newRow = (row + i + mapa->getRows()) % mapa->getRows();
                int newCol = (col + j + mapa->getCols()) % mapa->getCols();
                if (mapa->getMapa()[newRow][newCol].getTipo() == Localizacoes::Deserto ||
                    mapa->getMapa()[newRow][newCol].getTipo() == Localizacoes::Cidade) {
                    targetRow = newRow;
                    targetCol = newCol;
                    found = true;
                    }
            }
        }
        if (!found) {
            targetRow = row;
            targetCol = col;
        }
        }

    if (targetRow != row || targetCol != col) {
        consomeAgua();
        if (targetRow == row && targetCol == col + 1) setLastDirection("D");
        else if (targetRow == row && targetCol == col - 1) setLastDirection("E");
        else if (targetRow == row - 1 && targetCol == col) setLastDirection("C");
        else if (targetRow == row + 1 && targetCol == col) setLastDirection("B");
        else if (targetRow == row - 1 && targetCol == col - 1) setLastDirection("CE");
        else if (targetRow == row - 1 && targetCol == col + 1) setLastDirection("CD");
        else if (targetRow == row + 1 && targetCol == col - 1) setLastDirection("BE");
        else if (targetRow == row + 1 && targetCol == col + 1) setLastDirection("BD");
    }

    int res = mapa->move(this, targetRow, targetCol);
    return res;
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

    if (this->getAgua() == 0) {
        this->setTripulantes(tripulacao-1);
        return;
    }

    if (tripulacao >= maxTrip / 2)
        aguaConsumida = 3;
    else
        aguaConsumida = 1;

    this->setAgua(this->getAgua() - aguaConsumida);
}


int CaravanaMilitar::lastMoves(Mapa *mapa) {
    auto[row, col] = this->getCoordenadas(mapa);
    setComportamento(true);
    int newRow = row, newCol = col;

    string lastDirection = getLastDirection();

    if (lastDirection == "D")
        newCol = (col + 1 + mapa->getCols()) % mapa->getCols();
    else if (lastDirection == "E")
        newCol = (col - 1 + mapa->getCols()) % mapa->getCols();
    else if (lastDirection == "B")
        newRow = (row + 1 + mapa->getRows()) % mapa->getRows();
    else if (lastDirection == "C")
        newRow = (row - 1 + mapa->getRows()) % mapa->getRows();
    else if (lastDirection == "BE") {
        newRow = (row + 1 + mapa->getRows()) % mapa->getRows();
        newCol = (col - 1 + mapa->getCols()) % mapa->getCols();
    } else if (lastDirection == "BD") {
        newRow = (row + 1 + mapa->getRows()) % mapa->getRows();
        newCol = (col + 1 + mapa->getCols()) % mapa->getCols();
    } else if (lastDirection == "CE") {
        newRow = (row - 1 + mapa->getRows()) % mapa->getRows();
        newCol = (col - 1 + mapa->getCols()) % mapa->getCols();
    } else if (lastDirection == "CD") {
        newRow = (row - 1 + mapa->getRows()) % mapa->getRows();
        newCol = (col + 1 + mapa->getCols()) % mapa->getCols();
    }

    int res = mapa->move(this, newRow, newCol);
    this->setDeathCount(this->getDeathCount() - 1);
    return res;
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


std::string CaravanaMilitar::getLastDirection() const {
    return lastDirection;
}

void CaravanaMilitar::setLastDirection(const string &ld) {
    lastDirection = ld;
}

