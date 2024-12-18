//
// Created by rodrigo on 30-11-2024.
//

#include <stdexcept>
#include "Cidade.h"

std::set<char> Cidade::usedIds;

Cidade::Cidade(char id_, int pv, int pc, int pcav): id(generateUniqueId(id_)), prVenda(pv), prCompra(pc), prCaravana(pcav) {

}


char Cidade::getId() const {
    return id;
}


char Cidade::generateUniqueId(char preferredId) {
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