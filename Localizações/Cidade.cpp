//
// Created by rodrigo on 30-11-2024.
//
#include <set>
#include <stdexcept>
#include "Cidade.h"
#include "Caravana.h"
#include <string>
#include "../Mapa/Mapa.h"
#include <iostream>
#include <sstream>
using namespace std;

Cidade::Cidade(char id_, int pv, int pc, int pcav): id(generateUniqueId(id_)), prVenda(pv), prCompra(pc), prCaravana(pcav) {

}


char Cidade::getId() const {
    return id;
}


char Cidade::generateUniqueId(const char preferredId) {
    std::set<char> usedIds;
    if (preferredId != '\0' && !usedIds.contains(preferredId)) {
        usedIds.insert(preferredId);
        return preferredId;
    }
    for (char c = 'a'; c <= 'z'; ++c) {
        if (!usedIds.contains(c)) {
            usedIds.insert(c);
            return c;
        }
    }
    throw std::runtime_error("Ja nao ha mais ids disponiveis.");
}

bool Cidade::chegou_caravana(const Caravana *car) {
    for (auto &cars: caravanas_) {
        if (cars == car)
            return false;
    }
    caravanas_.push_back(car->duplica());
    return true;
}

Caravana *Cidade::isHere(char id) const {
    for (auto &car: caravanas_) {
        if (car->getId() == id)
            return car;
    }
    return nullptr;
}


string Cidade::listCaravanas() const {
    ostringstream oss;
    if (caravanas_.empty())
        oss << "Nenhuma caravana presente na cidade '" << this->getId() << "'.\n";
    else {
        oss << "Estao presentes na cidade '" << this->getId() << "' as caravanas:\n";
        for (auto &car: caravanas_) {
            oss << "- ";
            if (car->getTipo() == Tipos::Comercio) oss << "Caravana de Comercio ";
            else if (car->getTipo() == Tipos::Barbara) oss << "Caravana Barbara ";
            else if (car->getTipo() == Tipos::Militar) oss << "Caravana Militar ";

            oss << car->getId() << endl;
        }
    }
    return oss.str();
}

bool Cidade::sai_caravana(const char id) {
    vector<Caravana*>::iterator it = caravanas_.begin();
    while (it != caravanas_.end()) {
        if ((*it)->getId() == id) {
            caravanas_.erase(it);
            return true;
        }
        ++it;
    }
    return false;
}


Cidade &Cidade::operator=(const Cidade &outro) {
    if (this == &outro)
        return *this;

    id = outro.getId();
    prCaravana = outro.prCaravana;
    prCompra = outro.prCompra;
    prVenda = outro.prVenda;

    for (auto &car: caravanas_)
        delete car;
    caravanas_.clear();

    for (int i=0; i<outro.caravanas_.size(); ++i)
        caravanas_.push_back(outro.caravanas_[i]->duplica());

    return *this;
}


std::pair<int, int> Cidade::getCoordenadas(const Mapa *mapa) const {
    for (int row = 0; row < mapa->getRows(); ++row) {
        for (int col = 0; col < mapa->getCols(); ++col) {
            if (mapa->getMapa()[row][col].getTipo() == Localizacoes::Cidade) {
                if (mapa->getMapa()[row][col].getCidade() == this) {
                    return make_pair(row, col);
                }
            }
        }
    }
    return make_pair(-1, -1);
}
