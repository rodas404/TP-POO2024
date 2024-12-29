//
// Created by rodrigo on 28-12-2024.
//

#ifndef CARAVANASECRETA_H
#define CARAVANASECRETA_H
#include "../Localizações/Caravana.h"


class CaravanaSecreta: public Caravana{
public:
    CaravanaSecreta(char id_ = '\0');

    CaravanaSecreta* duplica() const override;

    void move(Mapa *mapa, std::string &direction) override;
    void move(Mapa *mapa) override;
    void lastMoves(Mapa *mapa) override;
    std::string getInfo() const override;
    void efeitoTempestade() override;

private:
    void consomeAgua() override;
};



#endif //CARAVANASECRETA_H
