//
// Created by rodrigo on 30-11-2024.
//
#include <iostream>
#include <sstream>
#include "Celula.h"
using namespace std;

Celula::Celula(const Localizacoes t): tipo(t), cidade_(nullptr), caravana_(nullptr), item_(nullptr)  {
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


void Celula::setTipo(const Localizacoes l) {
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

void Celula::resetItem() {
    item_ = nullptr;
}


Cidade *Celula::getCidade() const {
    return cidade_;
}

Item *Celula::getItem() const {
    return item_;
}


std::string Celula::getDescricao() const {
    ostringstream oss;
    if (this->getCaravana() != nullptr)
        oss << this->getCaravana()->getInfo();
    else if (this->getCidade() != nullptr)
        oss << this->getCidade()->listPrecos() << this->getCidade()->listCaravanas();
    else if (this->getItem() != nullptr)
        oss << this->getItem()->getDescricao();
    else if (this->getTipo() == Localizacoes::Montanha)
        oss << "Montanha" << endl;
    else
        oss << "Deserto" << endl;

    return oss.str();
}


std::ostream &operator<<(std::ostream &output, const Celula &c) {
    return output << c.getDescricao();
}


