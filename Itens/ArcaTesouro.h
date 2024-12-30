//
// Created by rodrigo on 18-12-2024.
//

#ifndef ARCATESOURO_H
#define ARCATESOURO_H
#include "../Localizacoes/Item.h"


class ArcaTesouro: public Item{
public:
    ArcaTesouro(int lifetime = 20);

    void action(Caravana *car) override;
    std::string getDescricao() const override;
};



#endif //ARCATESOURO_H
