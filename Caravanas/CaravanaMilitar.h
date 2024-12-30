//
// Created by rodrigo on 18-12-2024.
//

#ifndef CARAVANAMILITAR_H
#define CARAVANAMILITAR_H
#include "../Localizacoes/Caravana.h"


class CaravanaMilitar: public Caravana{
public:
    CaravanaMilitar(char id_ = '\0');
    CaravanaMilitar(const CaravanaMilitar &outro);
    CaravanaMilitar &operator=(const CaravanaMilitar &outro);
    CaravanaMilitar* duplica() const override;

    int move(Mapa *mapa, std::string &direction) override;
    int move(Mapa *mapa) override;
    int lastMoves(Mapa *mapa) override;
    std::string getInfo() const override;
    void efeitoTempestade() override;

    std::string getLastDirection() const;
    void setLastDirection(const std::string &ld);

private:
    void consomeAgua() override;
    std::string lastDirection;
};



#endif //CARAVANAMILITAR_H
