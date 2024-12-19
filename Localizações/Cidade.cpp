//
// Created by rodrigo on 30-11-2024.
//
#include <set>
#include <stdexcept>
#include "Cidade.h"
#include "Caravana.h"
#include <string>
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
    oss << "Estao presentes na cidade '" << this->getId() << "' as caravanas:\n";
    for (auto &car: caravanas_) {
        oss << "- " << car->getId() << endl;
    }
    return oss.str();
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
