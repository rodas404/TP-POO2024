//
// Created by rodrigo on 09-12-2024.
//

#ifndef CARAVANA_H
#define CARAVANA_H
#include <string>
#include <set>
class Mapa;

enum class Tipos {
    Comercio,
    Militar,
    Barbara
};

class Caravana {
public:
    //construtores
    Caravana(char id_, int trip, float carga, int agua, bool comportamento, int dc, int maxT, Tipos t);
    Caravana &operator=(const Caravana &outro);
    Caravana(const Caravana &outro);
    virtual Caravana* duplica() const = 0;
    virtual ~Caravana();

    //getters
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
    static float getMoedas();

    //setters
    void setTripulantes(int p);
    void setMercadorias(float t);
    void setAgua(int l);
    void setComportamento(bool c);
    void setDeathCount(int dc);
    static void setMoedas(float m);

    //operadores
    bool operator==(const Caravana &outro) const;

    //metodos
    std::pair<int, int> getCoordenadas(const Mapa *mapa) const;
    virtual void move(Mapa* mapa, std::string &direction); //move com instrucoes
    virtual void move(Mapa *mapa) = 0; //move sem instrucoes
    virtual void lastMoves(Mapa *mapa) = 0;
    virtual std::string getInfo() const;
    virtual void efeitoTempestade() = 0;

    static Caravana* find(const Mapa *mapa, char id);

private:
    char id; //id da caravana (char porque pode ser "numero" ou letra maiuscula
    int nTripulantes; //numero atual de tripulantes da caravana
    int maxTripulacao; // tripulação maxima da caravana
    float pMercadorias; //mercadorias que a caravana esta a carregar
    float maxMercadorias; //capacidade da caravana para carregar mercadorias
    int qAgua; //quantidade de agua que a caravana carrega
    int maxAgua; //capacidade de agua do deposito
    int deathCount; //quantos instantes faltam para a caravana desaparecer (só conta quando fica sem tripulação)
    bool compAleatorio; //true se esta a mover aleatoriamente, false se recebe instruções
    Tipos tipo; //tipo de caravana
    static float moedas; //moedas que o utilizador tem (comum a todas as caravanas)


    static char generateUniqueId(char preferredId); //função para gerir os ids
    static std::set<char> usedIds; //ids ja utilizados

    virtual void consomeAgua() = 0; //função para calcular o consumo de agua de cada caravana, privada porque é para apenas consumo interno
};

std::ostream &operator<<(std::ostream &output, const Caravana &car);



#endif //CARAVANA_H
