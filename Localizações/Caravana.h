//
// Created by rodrigo on 09-12-2024.
//

#ifndef CARAVANA_H
#define CARAVANA_H
#include <string>
class Mapa;

enum class Tipos {
    Comercio,
    Militar,
    Barbara
};

class Caravana {
public:
    Caravana(char id_, int trip, float carga, int agua, bool comportamento, int dc, int maxT, Tipos t);
    Caravana &operator=(const Caravana &outro);
    Caravana(const Caravana &outro);
    virtual Caravana* duplica() const = 0;
    virtual ~Caravana() = default;

    char getId() const;
    int getTripulantes() const;
    int getMaxTrip() const;
    float getMercadorias() const;
    float getMaxMerc() const;
    int getAgua() const;
    int getMaxAgua() const;
    bool getComportamento() const;
    int getDeathCount() const;
    Tipos getTipo() const;

    void setTripulantes(int p);
    void setMercadorias(float t);
    void setAgua(int l);
    void setComportamento(bool c);
    void setDeathCount(int dc);

    bool operator==(const Caravana &outro) const;

    std::pair<int, int> getCoordenadas(const Mapa *mapa) const;
    virtual void move(Mapa* mapa, std::string &direction); //move com instrucoes
    virtual void move(Mapa *mapa) = 0; //move sem instrucoes
    virtual void lastMoves(Mapa *mapa) = 0;
    virtual std::string getInfo() const;

    static Caravana* find(const Mapa *mapa, char id);

private:
    char id;
    int nTripulantes;
    int maxTripulacao;
    float pMercadorias;
    float maxMercadorias;
    int qAgua;
    int maxAgua;
    int deathCount;
    bool compAleatorio;
    Tipos tipo;

    static char generateUniqueId(char preferredId);
    virtual void consomeAgua() = 0;
};



#endif //CARAVANA_H
