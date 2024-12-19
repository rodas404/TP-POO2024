//
// Created by rodrigo on 09-12-2024.
//
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <stdexcept>
#include "Caravana.h"
#include "../Mapa/Mapa.h"
using namespace std;

Caravana::Caravana(char id_, int t, float carga, int agua, bool comp, float m, int dc): id(generateUniqueId(id_)), moedas(m), nTripulantes(t), pMercadorias(0), maxMercadorias(carga), qAgua(agua), maxAgua(agua), deathCount(dc), compAleatorio(comp) {

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

Caravana::Caravana(const Caravana &outro): id(outro.id), moedas(outro.moedas), nTripulantes(outro.nTripulantes), pMercadorias(outro.pMercadorias), maxMercadorias(outro.maxMercadorias), qAgua(outro.qAgua), maxAgua(outro.maxAgua), compAleatorio(outro.compAleatorio) {

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
    throw std::runtime_error("Sem ids disponiveis.");
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

float Caravana::getMercadorias() const {
    return pMercadorias;
}

int Caravana::getTripulantes() const {
    return nTripulantes;
}

float Caravana::getMoedas() const {
    return moedas;
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


bool Caravana::operator==(const Caravana &outro) const {
    return this->getId() == outro.getId();
}

std::string Caravana::getInfo() const {
    ostringstream oss;
    oss << "Moedas: " << this->getMoedas() <<
        "\nNum de Tripulantes: " << this->getTripulantes() <<
            "\nToneladas de Mercadoria: " << this->getMercadorias() <<
                "\nLitros de Agua: " << this->getAgua() <<
                    "\nComportamento automatico? " << (this->getComportamento() == true ? "sim" : "nao") << endl;
    return oss.str();

}

Caravana *Caravana::find(const Mapa *mapa, char id) {
    for (int x = 0; x < mapa->getRows(); ++x) {
        for (int y = 0; y < mapa->getCols(); ++y) {
            if (mapa->getMapa()[x][y].getTipo() == Localizacoes::Caravana) {
                if (mapa->getMapa()[x][y].getCaravana()->getId() == id) {
                    return mapa->getMapa()[x][y].getCaravana();
                }
            } else if (mapa->getMapa()[x][y].getTipo() == Localizacoes::Cidade) {
                if (mapa->getMapa()[x][y].getCidade()->isHere(id) != nullptr) {
                    return mapa->getMapa()[x][y].getCidade()->isHere(id);
                }
            }
        }
    }
    return nullptr;
}


void Caravana::move(Mapa *mapa, std::string &direction) {
    int col, row = 0;
    bool found = false;

    for (col = 0; col < mapa->getRows(); ++col) {
        for (row = 0; row < mapa->getCols(); ++row) {
            if (mapa->getMapa()[col][row].getTipo() == Localizacoes::Caravana) {
                if (mapa->getMapa()[col][row].getCaravana() == this) {
                    found = true;
                    break;
                }
            } else if (mapa->getMapa()[col][row].getTipo() == Localizacoes::Cidade) {
                if (mapa->getMapa()[col][row].getCidade()->isHere(this->getId()) != nullptr) {
                    found = true;
                    break;
                }
            }
        }
        if (found) break;
    }
    if (direction == "BE")
        mapa->move(col,row, col+1, row-1);
    else if (direction == "BD")
        mapa->move(col,row, col+1, row+1);
    else if (direction == "CE")
        mapa->move(col,row, col-1, row-1);
    else if (direction == "CD")
        mapa->move(col,row, col-1, row+1);
    else if (direction == "D")
        mapa->move(col,row, col, row+1);
    else if (direction == "E")
        mapa->move(col,row, col, row-1);
    else if (direction == "C")
        mapa->move(col,row, col-1, row);
    else if (direction == "B")
        mapa->move(col,row, col+1, row);
}


