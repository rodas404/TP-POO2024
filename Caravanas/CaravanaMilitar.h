//
// Created by rodrigo on 18-12-2024.
//

#ifndef CARAVANAMILITAR_H
#define CARAVANAMILITAR_H
#include "../Localizações/Caravana.h"


class CaravanaMilitar: public Caravana{
public:
    CaravanaMilitar(char id_, int m);

    CaravanaMilitar* duplica() const override;

    void move(Mapa *mapa, std::string &direction) override;
    std::string getInfo() const override;

private:
    int maxTripulantes;
};



#endif //CARAVANAMILITAR_H
