//
// Created by rodrigo on 30-11-2024.
//

#ifndef CIDADE_H
#define CIDADE_H
#include <vector>
#include <array>
#include <string>

class Caravana;
class Mapa;

class Cidade {
public:
    Cidade(char id_);
    Cidade(const Cidade &outro);
    Cidade &operator=(const Cidade &outro);

    char getId() const;
    static int getPrVenda() ;
    static int getPrCompra() ;
    static int getPrCaravana() ;

    static void setPrVenda(int pr);
    static void setPrCompra(int pr);
    static void setPrCaravana(int pr);

    bool chegou_caravana(const Caravana *car);
    Caravana* isHere(char id) const;
    static Cidade* find(const Mapa *mapa, char id);
    static Cidade* find(const Mapa *mapa, const Caravana *car);
    std::pair<int, int> getCoordenadas(const Mapa *mapa) const;
    std::string listCaravanas() const;
    static std::string listPrecos() ;
    bool sai_caravana(char id);
    bool vende(char id) const;
    bool compra(char id, float t) const; //compra mercadoria
    int compra(char tipo); //compra caravana
    bool compra(char id, int nt) const; //compra tripulantes
    int caravanasEstacionadas() const;

private:
    char id;
    static int prVenda;
    static int prCompra;
    static int prCaravana;
    std::vector <Caravana*> caravanas_;
    std::array <bool, 3> comprada; //array para monotorizar as caravanas compradas

    static char generateUniqueId(char preferredId);
};



#endif //CIDADE_H
