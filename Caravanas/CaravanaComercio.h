//
// Created by rodrigo on 18-12-2024.
//

#ifndef CARAVANACOMERCIO_H
#define CARAVANACOMERCIO_H
#include "../Localizações/Caravana.h"


class CaravanaComercio: public Caravana{
public:
    CaravanaComercio(char id_, int m);

    CaravanaComercio* duplica() const override;

    void move(Mapa *mapa) override;
};



#endif //CARAVANACOMERCIO_H
