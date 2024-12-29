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

float Caravana::moedas = 0.0f;
std::set<char> Caravana::usedIds;

Caravana::Caravana(const char id_, const int trip, const float carga, const int agua, const bool comportamento, const int dc, const int maxT, const Tipos t, const int nm): id(generateUniqueId(id_)), nTripulantes(trip), maxTripulacao(maxT), pMercadorias(0), maxMercadorias(carga), qAgua(agua), maxAgua(agua), deathCount(dc), compAleatorio(comportamento), tipo(t), nMoves(nm) {

}

Caravana &Caravana::operator=(const Caravana &outro) {
    if (this == &outro)
        return *this;

    id = outro.id;
    nTripulantes = outro.nTripulantes;
    maxTripulacao = outro.maxTripulacao;
    pMercadorias = outro.pMercadorias;
    maxMercadorias = outro.maxMercadorias;
    qAgua = outro.qAgua;
    maxAgua = outro.maxAgua;
    deathCount = outro.deathCount;
    compAleatorio = outro.compAleatorio;
    tipo = outro.tipo;
    nMoves = outro.nMoves;

    return *this;
}

Caravana::Caravana(const Caravana &outro): id(outro.id), nTripulantes(outro.nTripulantes), maxTripulacao(outro.maxTripulacao), pMercadorias(outro.pMercadorias), maxMercadorias(outro.maxMercadorias), qAgua(outro.qAgua), maxAgua(outro.maxAgua), deathCount(outro.deathCount), compAleatorio(outro.compAleatorio), tipo(outro.tipo), nMoves(outro.nMoves) {

}

Caravana::~Caravana() {
    usedIds.erase(id);
}


char Caravana::generateUniqueId(const char preferredId) {
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



    throw std::runtime_error("Erro: Nao ha mais ids disponveis para criar caravanas.");
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

float Caravana::getMoedas() {
    return moedas;
}

int Caravana::getNMoves() const {
    return nMoves;
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

void Caravana::setMoedas(float m) {
    moedas = m;
}


int Caravana::getDeathCount() const {
    return deathCount;
}


void Caravana::setDeathCount(const int dc) {
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
                               "\nCapacidade de Agua do Deposito: " << this->getMaxAgua() <<
                                   "\nComportamento automatico? " << (this->getComportamento() == true ? "Sim" : "Nao") <<
                                       "\nInstantes para morte: "<< this->getDeathCount() <<
                                           "\nMovimentos por turno: " << this->getNMoves() <<
                                               "\nMoedas: " << getMoedas() << endl;
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


int Caravana::move(Mapa *mapa, std::string &direction) {
    std::pair<int, int> coordinates = getCoordenadas(mapa);
    int row = coordinates.first;
    int col = coordinates.second;
    int res;

    if (row == -1 && col == -1)
        return -1;

    if (direction == "BE" || direction == "be")
        res = mapa->move(this, row + 1, col - 1);
    else if (direction == "BD" || direction == "bd")
        res = mapa->move(this, row + 1, col + 1);
    else if (direction == "CE" || direction == "ce")
        res = mapa->move(this, row - 1, col - 1);
    else if (direction == "CD" || direction == "cd")
        res = mapa->move(this, row - 1, col + 1);
    else if (direction == "D" || direction == "d")
        res = mapa->move(this, row, col+1);
    else if (direction == "E" || direction == "e")
        res = mapa->move(this, row, col-1);
    else if (direction == "C" || direction == "c")
        res = mapa->move(this, row-1, col);
    else if (direction == "B" || direction == "b")
        res = mapa->move(this, row+1, col);
    else
        return -1;
    return res;
}



std::ostream &operator<<(std::ostream &output, const Caravana &car) {
    output << car.getInfo();
    return output;
}

