//
// Created by rodrigo on 19-12-2024.
//

#ifndef PACOTESUSPENSO_H
#define PACOTESUSPENSO_H
#include "../Localizações/Item.h"


class PacoteSuspenso: public Item{
public:
    PacoteSuspenso();

    PacoteSuspenso *duplica() const override;
    void action(Caravana *car) override;
};



#endif //PACOTESUSPENSO_H
