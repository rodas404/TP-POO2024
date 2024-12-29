//
// Created by rodrigo on 18-12-2024.
//

#ifndef CARAVANAMILITAR_H
#define CARAVANAMILITAR_H
#include "../Localizações/Caravana.h"


class CaravanaMilitar: public Caravana{
public:
    CaravanaMilitar(char id_ = '\0');

    CaravanaMilitar* duplica() const override;

    void move(Mapa *mapa, std::string &direction) override;
    void move(Mapa *mapa) override;
    void lastMoves(Mapa *mapa) override;
    std::string getInfo() const override;
    void efeitoTempestade() override;

    std::string getLastDirection() const;
    void setLastDirection(const std::string &ld);

private:
    void consomeAgua() override;
    std::string lastDirection;
};



#endif //CARAVANAMILITAR_H
