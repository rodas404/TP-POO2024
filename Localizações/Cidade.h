//
// Created by rodrigo on 30-11-2024.
//

#ifndef CIDADE_H
#define CIDADE_H
#include <vector>
#include <string>

class Caravana;
class Mapa;

class Cidade {
public:
    Cidade(char id_, int pv, int pc, int pcav);
    Cidade(const Cidade &outro);
    Cidade &operator=(const Cidade &outro);

    char getId() const;
    int getPrVenda() const;
    int getPrCompra() const;
    int getPrCaravana() const;

    bool chegou_caravana(const Caravana *car);
    Caravana* isHere(char id) const;
    static Cidade* find(const Mapa *mapa, char id);
    static Cidade* find(const Mapa *mapa, const Caravana *car);
    static Cidade* find(const Mapa *mapa);
    std::pair<int, int> getCoordenadas(const Mapa *mapa) const;
    std::string listCaravanas() const;
    std::string listPrecos() const;
    bool sai_caravana(char id);
    bool vende(char id) const;
    bool compra(char id, float t) const; //compra mercadoria
    bool compra(char tipo); //compra caravana
    bool compra(char id, int nt) const; //compra tripulantes

private:
    char id;
    int prVenda;
    int prCompra;
    int prCaravana;
    std::vector <Caravana*> caravanas_;

    static char generateUniqueId(char preferredId);
};



#endif //CIDADE_H
