//
// Created by rodrigo on 08-12-2024.
//
#include "Item.h"
#include "../Mapa/Mapa.h"
using namespace std;
std::set<int> Item::usedIds;

Item::Item(int lifeTime): id(manageIds()), timeLeft(lifeTime) {
    usedIds.insert(id);
}


Item &Item::operator--() {
    if (timeLeft > 0)
        timeLeft--;
    return *this;
}

Item &Item::operator=(const Item &outro) {
    if (this == &outro)
        return *this;

    id = outro.id;
    timeLeft = outro.timeLeft;

    return *this;
}

int Item::getTimeLeft() const {
    return timeLeft;
}

Item::Item(const Item &outro): id(outro.getId()), timeLeft(outro.timeLeft) {

}

int Item::getId() const {
    return id;
}

int Item::manageIds() {
    int newId = 1;
    while (usedIds.contains(newId))
        newId++;
    return newId;
}

Item::~Item() {
    usedIds.erase(id);
}


std::pair<int, int> Item::getCoordenadas(const Mapa *mapa) const {
    for (int row = 0; row < mapa->getRows(); ++row) {
        for (int col = 0; col < mapa->getCols(); ++col) {
            if (mapa->getMapa()[row][col].getTipo() == Localizacoes::Item) {
                if (mapa->getMapa()[row][col].getItem() == this) {
                    return make_pair(row, col);
                }
            }
        }
    }
    return make_pair(-1, -1);
}


