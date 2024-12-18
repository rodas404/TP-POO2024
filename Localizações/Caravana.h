//
// Created by rodrigo on 09-12-2024.
//

#ifndef CARAVANA_H
#define CARAVANA_H
#include <set>


class Caravana {
public:
    Caravana(char id_);
    char getId() const;
    Caravana &operator=(const Caravana &outro);
    Caravana(const Caravana &outro);
private:
    char id;
    // int quantAtualTripulantes;
    // int quantMaxTripulantes;
    // float pesoMaxMercadoria;
    // float pesoAtualMercadoria;
    // float quantMaxAgua;
    // float quantAtualAgua;

    static char generateUniqueId(char preferredId);
};



#endif //CARAVANA_H
