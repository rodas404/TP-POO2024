//
// Created by rodrigo on 18-12-2024.
//

#ifndef CARAVANACOMERCIO_H
#define CARAVANACOMERCIO_H
#include "../Localizacoes/Caravana.h"


class CaravanaComercio: public Caravana{
public:
    CaravanaComercio(char id_ = '\0');
    CaravanaComercio(const CaravanaComercio &outro);
    CaravanaComercio &operator=(const CaravanaComercio &outro);
    CaravanaComercio* duplica() const override;

    int move(Mapa *mapa, std::string &direction) override;
    int move(Mapa *mapa) override;
    int lastMoves(Mapa *mapa) override;
    std::string getInfo() const override;
    void efeitoTempestade() override;

private:
    void consomeAgua() override;
};



#endif //CARAVANACOMERCIO_H
