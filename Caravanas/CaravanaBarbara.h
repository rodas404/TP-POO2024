//
// Created by rodrigo on 19-12-2024.
//

#ifndef CARAVANABARBARA_H
#define CARAVANABARBARA_H
#include "../Localizações/Caravana.h"


class CaravanaBarbara: public Caravana{
public:
    CaravanaBarbara(int lifetime = 60);

    CaravanaBarbara *duplica() const override;
    void move(Mapa *mapa) override;
    void lastMoves(Mapa *mapa) override;
    void efeitoTempestade() override;
private:
    void consomeAgua() override;
};



#endif //CARAVANABARBARA_H
