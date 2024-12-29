//
// Created by rodrigo on 18-12-2024.
//

#ifndef CAIXAPANDORA_H
#define CAIXAPANDORA_H
#include "../Localizações/Item.h"


class CaixaPandora: public Item{
public:
    CaixaPandora(int lifetime = 20);
    void action(Caravana *car) override;
    std::string getDescricao() const override;
};



#endif //CAIXAPANDORA_H
