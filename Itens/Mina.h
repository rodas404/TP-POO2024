//
// Created by rodrigo on 18-12-2024.
//

#ifndef MINA_H
#define MINA_H
#include "../Localizações/Item.h"


class Mina: public Item{
public:
    Mina();
    std::string getDescricao() const override;
    void action(Caravana *car) override;
};



#endif //MINA_H
