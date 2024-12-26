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
    Cidade* getCidade() const;
    Item* getItem() const;

    void resetCaravana();
    void resetItem();
    void setTipo(Localizacoes l);
    Localizacoes getTipo() const;
    bool checkRestricoes() const;
    std::string getDescricao() const;

    Celula& operator=(const Celula& other);
private:
    Localizacoes tipo;
    Cidade* cidade_;
    Caravana* caravana_;
    Item* item_;
};

std::ostream &operator<<(std::ostream &output, const Celula &c);

#endif //CELULA_H
