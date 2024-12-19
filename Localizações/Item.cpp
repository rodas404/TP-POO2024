//
// Created by rodrigo on 08-12-2024.
//

#include "Item.h"

int Item::lifetime = 20;

Item::Item(): id('?'), timeLeft(lifetime) {

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

int Item::setLifeTime(const int time) {
    lifetime = time;
    return lifetime;
}


char Item::getId() const {
    return id;
}

