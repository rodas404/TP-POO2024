//
// Created by rodrigo on 18-12-2024.
//

#ifndef CARAVANAMILITAR_H
#define CARAVANAMILITAR_H
#include "../Localizações/Caravana.h"


class CaravanaMilitar: public Caravana{
public:
    CaravanaMilitar(char id_);

    CaravanaMilitar* duplica() const override;

    void move(Mapa *mapa, std::string &direction) override;
    void move(Mapa *mapa) override;
    void lastMoves(Mapa *mapa) override;
    std::string getInfo() const override;
private:
    void consomeAgua() override;
};



#endif //CARAVANAMILITAR_H
