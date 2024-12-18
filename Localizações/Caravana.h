//
// Created by rodrigo on 09-12-2024.
//

#ifndef CARAVANA_H
#define CARAVANA_H

class Mapa;

class Caravana {
public:
    Caravana(char id_, int t, float carga, int agua, bool comportamento, int m);
    Caravana &operator=(const Caravana &outro);
    Caravana(const Caravana &outro);
    virtual Caravana* duplica() const = 0;
    virtual ~Caravana() = default;

    char getId() const;
    int getTripulantes() const;
    float getMercadorias() const;
    float getMaxMerc() const;
    int getAgua() const;
    bool getComportamento() const;
    int getMoedas() const;

    void setTripulantes(int p);
    void setMercadorias(float t);
    void setAgua(int l);
    void setComportamento(bool c);
    void setMoedas(int m);

    virtual void move(Mapa* mapa) = 0;


private:
    char id;
    int moedas;
    int nTripulantes;
    float pMercadorias;
    float maxMercadorias;
    int qAgua;
    int maxAgua;
    bool compAleatorio;

    static char generateUniqueId(char preferredId);
};



#endif //CARAVANA_H
