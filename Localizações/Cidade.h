//
// Created by rodrigo on 30-11-2024.
//

#ifndef CIDADE_H
#define CIDADE_H
#include <vector>
#include <set>
#include "Caravana.h"


class Cidade {
public:
    Cidade(char id_, int pv, int pc, int pcav);
    char getId() const;
private:
    char id;
    int prVenda;
    int prCompra;
    int prCaravana;
    std::vector <Caravana*> caravanas_;

    static char generateUniqueId(char preferredId);
};



#endif //CIDADE_H
