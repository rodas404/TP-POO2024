//
// Created by rodrigo on 09-12-2024.
//

#ifndef CARAVANA_H
#define CARAVANA_H
#include <string>
class Mapa;

class Caravana {
public:
    Caravana(char id_, int t, float carga, int agua, bool comportamento, float m, int dc);
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
    float getMoedas() const;

    void setTripulantes(int p);
    void setMercadorias(float t);
    void setAgua(int l);
    void setComportamento(bool c);
    void setMoedas(float m);

    bool operator==(const Caravana &outro) const;

    virtual void move(Mapa* mapa, std::string &direction);
    virtual std::string getInfo() const;

    static Caravana* find(const Mapa *mapa, char id);

private:
    char id;
    float moedas;
    int nTripulantes;
    float pMercadorias;
    float maxMercadorias;
    int qAgua;
    int maxAgua;
    int deathCount;
    bool compAleatorio;

    static char generateUniqueId(char preferredId);
};



#endif //CARAVANA_H
