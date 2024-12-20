//
// Created by rodrigo on 18-12-2024.
//

#ifndef JAULA_H
#define JAULA_H
#include "../Localizações/Item.h"


class Jaula: public Item{
public:
    Jaula();
    void action(Caravana *car) override;
};



#endif //JAULA_H
