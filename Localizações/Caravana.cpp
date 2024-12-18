//
// Created by rodrigo on 09-12-2024.
//
#include <iostream>
#include <stdexcept>
#include "Caravana.h"
using namespace std;

Caravana::Caravana(char id_): id(generateUniqueId(id_))  {

}

char Caravana::getId() const {
    return id;
}

Caravana &Caravana::operator=(const Caravana &outro)  {
    if (this == &outro)
        return *this;

    id = outro.id;

    return *this;
}

Caravana::Caravana(const Caravana &outro): id(outro.id) {

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
    throw std::runtime_error("No more unique IDs available.");
}
