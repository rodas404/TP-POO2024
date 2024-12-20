//
// Created by rodrigo on 18-12-2024.
//

#ifndef CARAVANACOMERCIO_H
#define CARAVANACOMERCIO_H
#include "../Localizações/Caravana.h"


class CaravanaComercio: public Caravana{
public:
    CaravanaComercio(char id_);

    CaravanaComercio* duplica() const override;

    void move(Mapa *mapa, std::string &direction) override;
    void move(Mapa *mapa) override;
    void lastMoves(Mapa *mapa) override;
    std::string getInfo() const override;

private:
    void consomeAgua() override;
};



#endif //CARAVANACOMERCIO_H
