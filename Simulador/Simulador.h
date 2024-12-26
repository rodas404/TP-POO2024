//
// Created by rodrigo on 19-12-2024.
//

#ifndef SIMULADOR_H
#define SIMULADOR_H
#include <map>
#include <string>

class Celula;
class Buffer;
class Mapa;

class Simulador {
public:
    Simulador();
    Simulador(const Simulador &outro);
    Simulador &operator=(const Simulador &outro);

    Mapa* getMapa() const;
    int getInstantesItens() const;
    int getLifetimeItens() const;
    int getMaxItens() const;
    int getInstantesBarbaros() const;
    int getBarbarosLifetime() const;
    bool getRunning() const;
    bool getTurnRunning() const;

    void setRunning(bool r);
    void setTurnRunning(bool tr);

    static Simulador readFile(const std::string &fileName);
    void run();
    void executeInstant();
    void executeTurn();

    bool insere_buffer(const std::string &nome, const Buffer& buffer);
    bool remove_buffer(const std::string& nome);
    std::string get_buffer(std::string nome);
    std::string list_buffers() const;
    void readCommand();

    Celula &operator()(int row, int col) const;

private:
    Mapa *mapa_;
    int instantes_itens;
    int lifetime_itens;
    int max_itens;
    int instantes_barbaros;
    int barbaros_lifetime;
    std::map<std::string, Buffer> buffers;

    bool running;
    bool turnRunning;
};



#endif //SIMULADOR_H
