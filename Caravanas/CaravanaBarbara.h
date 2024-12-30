//
// Created by rodrigo on 19-12-2024.
//

#ifndef CARAVANABARBARA_H
#define CARAVANABARBARA_H
#include "../Localizacoes/Caravana.h"


class CaravanaBarbara: public Caravana{
public:
    CaravanaBarbara(int lifetime = 60);
    CaravanaBarbara(const CaravanaBarbara &outro);
    CaravanaBarbara &operator=(const CaravanaBarbara &outro);

    CaravanaBarbara *duplica() const override;
    int move(Mapa *mapa) override;
    int lastMoves(Mapa *mapa) override;
    void efeitoTempestade() override;
    std::string getInfo() const override;
private:
    void consomeAgua() override;
};



#endif //CARAVANABARBARA_H
