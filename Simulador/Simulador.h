//
// Created by rodrigo on 19-12-2024.
//

#ifndef SIMULADOR_H
#define SIMULADOR_H
#include <map>
#include <string>

class Buffer;
class Mapa;

class Simulador {
public:
    Simulador();
    Simulador(const Simulador &outro);
    ~Simulador();
    Simulador &operator=(const Simulador &outro);

    Mapa* getMapa() const;
    int getInstantesItens() const;
    int getLifetimeItens() const;
    int getMaxItens() const;
    int getInstantesBarbaros() const;
    int getBarbarosLifetime() const;
    bool getRunning() const;
    bool getTurnRunning() const;
    int getCurrentInstant() const;
    int getVitorias() const;
    int getItensApanhados() const;

    void setRunning(bool r);
    void setTurnRunning(bool tr);
    void setCurrentInstant(int ci);
    void setVitorias(int n);
    void setItensApanhados(int n);

    static void start();
    static Simulador readFile(const std::string &fileName);
    void run();
    void executeInstant();
    void executeTurn();
    void isOver();

    bool insere_buffer(const std::string &nome, const Buffer& buffer);
    bool remove_buffer(const std::string& nome);
    std::string get_buffer(const std::string& nome);
    std::string list_buffers() const;
    int readCommand(const std::string &line);
    bool manageMoves(char id, int moves);
    void resetMoves();
    bool exec(const std::string &fileName);

private:
    Mapa *mapa_;
    int instantes_itens;
    int lifetime_itens;
    int max_itens;
    int instantes_barbaros;
    int barbaros_lifetime;
    std::map<std::string, Buffer> buffers;
    std::map<char, int> controlMoves;

    bool running;
    bool turnRunning;
    int currentInstant;
    int nItensApanhados;
    int nVitorias;
};

std::ostream &operator<<(std::ostream &output, const Simulador &s);

#endif //SIMULADOR_H
