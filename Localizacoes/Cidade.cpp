//
// Created by rodrigo on 30-11-2024.
//
#include <set>
#include <stdexcept>
#include "Cidade.h"

#include <array>
#include "Caravana.h"
#include <string>
#include "../Mapa/Mapa.h"
#include <iostream>
#include <sstream>

#include "../Caravanas/CaravanaComercio.h"
#include "../Caravanas/CaravanaMilitar.h"
#include "../Caravanas/CaravanaSecreta.h"
using namespace std;

int Cidade::prVenda = 0;
int Cidade::prCompra = 0;
int Cidade::prCaravana = 0;

Cidade::Cidade(const char id_): id(generateUniqueId(id_)), comprada({false, false, false}) {

}


Cidade::Cidade(const Cidade &outro): id(outro.id), comprada(outro.comprada) {
    for (int i=0; i<outro.caravanas_.size(); ++i)
        caravanas_.push_back(outro.caravanas_[i]->duplica());
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
    throw std::runtime_error("Erro: Nao ha mais ids disponiveis para criar cidades.");
}

bool Cidade::chegou_caravana(const Caravana *car) {
    for (const auto &cars: caravanas_) {
        if (cars == car)
            return false;
    }
    caravanas_.push_back(car->duplica());
    return true;
}

Caravana *Cidade::isHere(const char id) const {
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
            if (car->getTipo() == Tipos::Comercio) oss << "Caravana de Comercio '";
            else if (car->getTipo() == Tipos::Barbara) oss << "Caravana Barbara '";
            else if (car->getTipo() == Tipos::Militar) oss << "Caravana Militar '";
            else if (car->getTipo() == Tipos::Secreta) oss << "Caravana Secreta '";

            oss << car->getId() << "';\n";
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
    comprada = outro.comprada;

    for (auto &car: caravanas_)
        delete car;
    caravanas_.clear();

    for (int i = 0; i < outro.caravanas_.size(); ++i)
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


bool Cidade::vende(const char id) const {
    Caravana *car = isHere(id);
    if (car == nullptr)
        return false;

    float mercadorias = car->getMercadorias();
    float valorVenda = mercadorias * static_cast<float>(Cidade::getPrVenda());
    car->setMercadorias(0);

    float moedas = Caravana::getMoedas();
    Caravana::setMoedas(moedas + valorVenda);

    return true;
}

int Cidade::getPrCaravana() {
    return prCaravana;
}

int Cidade::getPrCompra() {
    return prCompra;
}

int Cidade::getPrVenda() {
    return prVenda;
}

void Cidade::setPrCaravana(const int pr) {
    prCaravana = pr;
}

void Cidade::setPrCompra(const int pr) {
    prCompra = pr;
}

void Cidade::setPrVenda(const int pr) {
    prVenda = pr;
}



std::string Cidade::listPrecos() {
    ostringstream oss;
    oss << "Precos praticados neste momento:\n" <<
        "- Venda de Mercadoria: " << getPrVenda() << "p/ton\n" <<
            "- Compra de Mercadoria: " << getPrCompra() << "p/ton\n" <<
                "- Compra de Caravana: " << getPrCaravana() << endl;
    return oss.str();
}


bool Cidade::compra(const char id, const float t) const {
    Caravana *car = isHere(id);
    if (car == nullptr)
        return false;

    float moedas = Caravana::getMoedas();
    float preco = t * static_cast<float>(Cidade::getPrCompra());

    if (preco > moedas)
        return false;

    Caravana::setMoedas(moedas - preco);
    car->setMercadorias(car->getMercadorias() + t);
    return true;
}

int Cidade::caravanasEstacionadas() const {
    return static_cast<int>(caravanas_.size());
}


int Cidade::compra(const char tipo) {
    float moedas = Caravana::getMoedas();
    float preco = static_cast<float>(getPrCaravana());

    if (preco > moedas)
        return -1;
    try {
        Caravana *car;
        if (tipo == 'C' || tipo == 'c') {
            if (comprada[0] == false) {
                car = new CaravanaComercio();
                comprada[0] = true;
            }
            else
                return 0;
        }
        else if (tipo == 'M' || tipo == 'm') {
            if (comprada[1] == false) {
                car = new CaravanaMilitar();
                comprada[1] = true;
            }
            else
                return 0;
        }
        else if (tipo == 'S' || tipo == 's') {
            if (comprada[2] == false) {
                car = new CaravanaSecreta();
                comprada[2] = true;
            }
            else
                return 0;
        }
        else
            return -2;

        Caravana::setMoedas(moedas - preco);
        this->chegou_caravana(car);
        return 1;
    } catch (const exception& e) {
        cout << e.what() << endl;
        return -1;
    }
}

bool Cidade::compra(const char id, const int nt) const {
    Caravana *car = isHere(id);
    if (car == nullptr)
        return false;

    float moedas = Caravana::getMoedas();
    float preco = static_cast<float>(nt * getPrCompra());

    if (preco > moedas)
        return false;

    Caravana::setMoedas(moedas - preco);
    car->setTripulantes(min(car->getTripulantes() + nt, car->getMaxTrip()));
    return true;
}


Cidade *Cidade::find(const Mapa *mapa, const char id) {
    for (int row = 0; row < mapa->getRows(); ++row) {
        for (int col = 0; col < mapa->getCols(); ++col) {
            if (mapa->getMapa()[row][col].getTipo() == Localizacoes::Cidade) {
                if (mapa->getMapa()[row][col].getCidade()->getId() == id) {
                    return mapa->getMapa()[row][col].getCidade();
                }
            }
        }
    }
    return nullptr;
}

Cidade *Cidade::find(const Mapa *mapa, const Caravana *car) {
    for (int row = 0; row < mapa->getRows(); ++row) {
        for (int col = 0; col < mapa->getCols(); ++col) {
            if (mapa->getMapa()[row][col].getTipo() == Localizacoes::Cidade) {
                if (mapa->getMapa()[row][col].getCidade()->isHere(car->getId()) != nullptr)
                    return mapa->getMapa()[row][col].getCidade();
            }
        }
    }
    return nullptr;
}



