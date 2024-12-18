//
// Created by rodrigo on 30-11-2024.
//

#ifndef CELULA_H
#define CELULA_H
#include "../Localizações/Cidade.h"
#include "../Localizações/Item.h"
#include <memory>

#include "../Localizações/Caravana.h"

enum class Localizacoes {
    Deserto,
    Cidade,
    Montanha,
    Caravana,
    Item
};


class Celula {
public:
    Celula(Localizacoes t = Localizacoes::Deserto);
    void setCelula();
    void setCelula(Cidade *c);
    void setCelula(Item *i);
    void setCelula(Caravana *car);

    Caravana* getCaravana() const;
    void resetCaravana();
    void setTipo(Localizacoes l);
    Localizacoes getTipo() const;
    bool checkRestricoes() const;

    Celula& operator=(const Celula& other);
private:
    Localizacoes tipo;
    Cidade* cidade_;
    Caravana* caravana_;
    Item* item_;
};



#endif //CELULA_H