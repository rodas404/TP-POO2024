//
// Created by rodrigo on 28-12-2024.
//

#ifndef CARAVANASECRETA_H
#define CARAVANASECRETA_H
#include "../Localizações/Caravana.h"


class CaravanaSecreta: public Caravana{
public:
    CaravanaSecreta(char id_ = '\0');
    CaravanaSecreta(const CaravanaSecreta &outro);
    CaravanaSecreta &operator=(const CaravanaSecreta &outro);
    CaravanaSecreta* duplica() const override;

    int move(Mapa *mapa, std::string &direction) override;
    int move(Mapa *mapa) override;
    int lastMoves(Mapa *mapa) override;
    std::string getInfo() const override;
    void efeitoTempestade() override;

private:
    void consomeAgua() override;
};



#endif //CARAVANASECRETA_H
