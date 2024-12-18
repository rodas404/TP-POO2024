//
// Created by rodrigo on 30-11-2024.
//
#include <iostream>
#include "Celula.h"
using namespace std;

Celula::Celula(Localizacoes t): tipo(t), cidade_(nullptr), caravana_(nullptr), item_(nullptr)  {
}

void Celula::setCelula() {
    setTipo(Localizacoes::Deserto);
}

void Celula::setCelula(Cidade *c) {
    cidade_ = c;
    setTipo(Localizacoes::Cidade);

}

void Celula::setCelula(Caravana *car) {
    caravana_ = car;
    setTipo(Localizacoes::Caravana);
}


bool Celula::checkRestricoes() const {
    if (tipo == Localizacoes::Montanha || tipo == Localizacoes::Cidade)
        return false;
    return true;
}


void Celula::setTipo(Localizacoes l) {
    tipo = l;
}

void Celula::setCelula(Item *i) {
    item_ = i;
    setTipo(Localizacoes::Item);
}

Localizacoes Celula::getTipo() const {
    return tipo;
}

Celula& Celula::operator=(const Celula &other) {
    if (this == &other)
        return *this;

    tipo = other.tipo;
    cidade_ = other.cidade_;
    caravana_ = other.caravana_;
    item_ = other.item_;

    return *this;
}


Caravana *Celula::getCaravana() const {
    return caravana_;
}

void Celula::resetCaravana() {
    caravana_ = nullptr;
}



