//
// Created bcol rodrigo on 09-12-2024.
//
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <stdexcept>
#include "Caravana.h"
#include "../Mapa/Mapa.h"
using namespace std;

Caravana::Caravana(const char id_, const int trip, const float carga, const int agua, const bool comp, const int dc, const int maxT, const Tipos t): id(generateUniqueId(id_)), nTripulantes(trip), maxTripulacao(maxT), pMercadorias(0), maxMercadorias(carga), qAgua(agua), maxAgua(agua), deathCount(dc), compAleatorio(comp), tipo(t) {

}

Caravana &Caravana::operator=(const Caravana &outro)  {
    if (this == &outro)
        return *this;

    id = outro.id;
    nTripulantes = outro.nTripulantes;
    pMercadorias = outro.pMercadorias;
    maxMercadorias = outro.maxMercadorias;
    qAgua = outro.qAgua;
    compAleatorio = outro.compAleatorio;

    return *this;
}

Caravana::Caravana(const Caravana &outro): id(outro.id), nTripulantes(outro.nTripulantes), maxTripulacao(outro.maxTripulacao), pMercadorias(outro.pMercadorias), maxMercadorias(outro.maxMercadorias), qAgua(outro.qAgua), maxAgua(outro.maxAgua), deathCount(outro.deathCount), compAleatorio(outro.compAleatorio), tipo(outro.tipo) {

}

char Caravana::generateUniqueId(const char preferredId) {
    static std::set<char> usedIds;

    if (preferredId != '\0' && !usedIds.contains(preferredId)) {
        usedIds.insert(preferredId);
        return preferredId;
    }

    for (char c = '0'; c <= '9'; ++c) {
        if (!usedIds.contains(c)) {
            usedIds.insert(c);
            return c;
        }
    }

    for (char c = 'A'; c <= 'Z'; ++c) {
        if (!usedIds.contains(c)) {
            usedIds.insert(c);
            return c;
        }
    }

    if (preferredId == '!')
        return '!';

    throw std::runtime_error("No available IDs.");
}


char Caravana::getId() const {
    return id;
}

int Caravana::getAgua() const {
    return qAgua;
}

bool Caravana::getComportamento() const {
    return compAleatorio;
}

Tipos Caravana::getTipo() const {
    return tipo;
}


float Caravana::getMercadorias() const {
    return pMercadorias;
}

int Caravana::getTripulantes() const {
    return nTripulantes;
}
int Caravana::getMaxAgua() const {
    return maxAgua;
}

int Caravana::getMaxTrip() const {
    return maxTripulacao;
}

float Caravana::getMaxMerc() const {
    return maxMercadorias;
}

void Caravana::setAgua(int l) {
    qAgua = l;
}

void Caravana::setComportamento(bool c) {
    compAleatorio = c;
}

void Caravana::setMercadorias(float t) {
    pMercadorias = t;
}

void Caravana::setTripulantes(int p) {
    nTripulantes = p;
}


int Caravana::getDeathCount() const {
    return deathCount;
}


void Caravana::setDeathCount(int dc) {
    deathCount = dc;
}


bool Caravana::operator==(const Caravana &outro) const {
    return this->getId() == outro.getId();
}

std::string Caravana::getInfo() const {
    ostringstream oss;
    oss << "Num de Tripulantes: " << this->getTripulantes() <<
            "\nTripulacao Maxima: " << this->getMaxTrip() <<
                 "\nToneladas de Mercadoria: " << this->getMercadorias() <<
                      "\nCapacidade de Carga: " << this->getMaxMerc() <<
                         "\nLitros de Agua: " << this->getAgua() <<
                               "\nCapacidade do Deposito: " << this->getMaxAgua() <<
                                   "\nComportamento automatico? " << (this->getComportamento() == true ? "sim" : "nao") << endl;
    return oss.str();

}

std::pair<int, int> Caravana::getCoordenadas(const Mapa *mapa) const {
    for (int row = 0; row < mapa->getRows(); ++row) {
        for (int col = 0; col < mapa->getCols(); ++col) {
            if (mapa->getMapa()[row][col].getTipo() == Localizacoes::Caravana) {
                if (mapa->getMapa()[row][col].getCaravana() == this) {
                    return make_pair(row, col);
                }
            } else if (mapa->getMapa()[row][col].getTipo() == Localizacoes::Cidade) {
                if (mapa->getMapa()[row][col].getCidade()->isHere(this->getId()) != nullptr) {
                    return make_pair(row, col);
                }
            }
        }
    }
    return make_pair(-1, -1);
}

Caravana *Caravana::find(const Mapa *mapa, const char id) {
    for (int row = 0; row < mapa->getRows(); ++row) {
        for (int col = 0; col < mapa->getCols(); ++col) {
            if (mapa->getMapa()[row][col].getTipo() == Localizacoes::Caravana) {
                if (mapa->getMapa()[row][col].getCaravana()->getId() == id) {
                    return mapa->getMapa()[row][col].getCaravana();
                }
            } else if (mapa->getMapa()[row][col].getTipo() == Localizacoes::Cidade) {
                if (mapa->getMapa()[row][col].getCidade()->isHere(id) != nullptr) {
                    return mapa->getMapa()[row][col].getCidade()->isHere(id);
                }
            }
        }
    }
    return nullptr;
}


void Caravana::move(Mapa *mapa, std::string &direction) {
    std::pair<int, int> coordinates = getCoordenadas(mapa);
    int row = coordinates.first;
    int col = coordinates.second;

    if (row == -1 && col == -1)
        return;

    if (direction == "BE")
        mapa->move(this, row + 1, col - 1);
    else if (direction == "BD")
        mapa->move(this, row + 1, col + 1);
    else if (direction == "CE")
        mapa->move(this, row - 1, col - 1);
    else if (direction == "CD")
        mapa->move(this, row - 1, col + 1);
    else if (direction == "D")
        mapa->move(this, row, col+1);
    else if (direction == "E")
        mapa->move(this, row, col-1);
    else if (direction == "C")
        mapa->move(this, row-1, col);
    else if (direction == "B")
        mapa->move(this, row+1, col);
}




