//
// Created by rodrigo on 18-12-2024.
//

#ifndef ARCATESOURO_H
#define ARCATESOURO_H
#include "../Localizações/Item.h"


class ArcaTesouro: public Item{
public:
    ArcaTesouro();

    void action(Caravana *car) override;
};



#endif //ARCATESOURO_H
