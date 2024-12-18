//
// Created by rodrigo on 09-12-2024.
//
#include <iostream>
#include <set>
#include <stdexcept>
#include "Caravana.h"
using namespace std;

Caravana::Caravana(char id_, int t, float carga, int agua, bool comp, int m): id(generateUniqueId(id_)), moedas(m), nTripulantes(t), pMercadorias(0), maxMercadorias(carga), qAgua(agua), maxAgua(agua), compAleatorio(comp) {

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

Caravana::Caravana(const Caravana &outro): id(outro.id), moedas(outro.moedas), nTripulantes(outro.nTripulantes), pMercadorias(outro.pMercadorias), maxMercadorias(outro.maxMercadorias), qAgua(outro.qAgua), compAleatorio(outro.compAleatorio), maxAgua(outro.maxAgua) {

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

int Caravana::getMoedas() const {
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

void Caravana::setMoedas(int m) {
    moedas = m;
}







