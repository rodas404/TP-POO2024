//
// Created by rodrigo on 30-11-2024.
//

#ifndef CIDADE_H
#define CIDADE_H
#include <vector>

class Caravana;


class Cidade {
public:
    Cidade(char id_, int pv, int pc, int pcav);
    Cidade(const Cidade &outro);
    Cidade &operator=(const Cidade &outro);

    char getId() const;

    bool chegou_caravana(const Caravana *car);
    Caravana* isHere(char id) const;
    std::string listCaravanas() const;
private:
    char id;
    int prVenda;
    int prCompra;
    int prCaravana;
    std::vector <Caravana*> caravanas_;

    static char generateUniqueId(char preferredId);
};



#endif //CIDADE_H
