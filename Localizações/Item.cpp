//
// Created by rodrigo on 08-12-2024.
//

#include "Item.h"


Item::Item(int lifeTime): id('?'), timeLeft(lifeTime) {

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

char Item::getId() const {
    return id;
}

