//
// Created by rodrigo on 18-12-2024.
//

#ifndef MINA_H
#define MINA_H
#include "../Localizações/Item.h"


class Mina: public Item{
public:
    Mina();

    void action(Caravana *car) override;
    Mina *duplica() const override;
};



#endif //MINA_H
