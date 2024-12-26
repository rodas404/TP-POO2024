//
// Created by rodrigo on 19-12-2024.
//
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <random>
#include <array>
#include "Simulador.h"
#include "../Mapa/Mapa.h"
#include "../Buffer/Buffer.h"
#include "../Localizações/Caravana.h"
#include "../Localizações/Cidade.h"
#include "../Caravanas/CaravanaComercio.h"
#include "../Caravanas/CaravanaMilitar.h"
#include "../Caravanas/CaravanaBarbara.h"

using namespace std;

Simulador::Simulador() : mapa_(nullptr), instantes_itens(0), lifetime_itens(0), max_itens(0), instantes_barbaros(0), barbaros_lifetime(0), running(false), turnRunning(false) {}

Simulador::Simulador(const Simulador &outro):mapa_(outro.mapa_),instantes_itens(outro.instantes_itens), lifetime_itens(outro.lifetime_itens), max_itens(outro.max_itens), instantes_barbaros(outro.instantes_barbaros), barbaros_lifetime(outro.barbaros_lifetime), buffers(outro.buffers), running(outro.running), turnRunning(outro.turnRunning) {
}
Simulador &Simulador::operator=(const Simulador &outro) {
    if (this == &outro)
        return *this;

    // Copy member variables
    instantes_itens = outro.instantes_itens;
    lifetime_itens = outro.lifetime_itens;
    max_itens = outro.max_itens;
    instantes_barbaros = outro.instantes_barbaros;
    barbaros_lifetime = outro.barbaros_lifetime;

    delete mapa_;
    mapa_ = outro.mapa_;

    buffers = outro.buffers;
    return *this;
}


Simulador Simulador::readFile(const string &fileName) {
    ifstream file(fileName);
    if (!file.is_open())
        throw runtime_error("Erro ao abrir ficheiro.");

    int nRows, nCols;
    string line, temp;

    // ler linhas
    getline(file, line);
    istringstream iss1(line);
    iss1 >> temp >> nRows;

    // ler colunas
    getline(file, line);
    istringstream iss2(line);
    iss2 >> temp >> nCols;

    // ler mapa
    vector<string> gridLines;
    for (int i = 0; i < nRows; ++i) {
        getline(file, line);
        gridLines.push_back(line);
    }

    // ler detalhes da simulação
    std::array<int, 9> details{};
    std::array<string, 9> detailNames = {
        "moedas", "instantes_entre_novos_itens", "duração_item", "max_itens",
        "preço_venda_mercadoria", "preço_compra_mercadoria", "preço_caravana",
        "instantes_entre_novos_barbaros", "duração_barbaros"
    };

    for (int i = 0; i < 9; ++i) {
        getline(file, line);
        istringstream iss(line);
        iss >> temp >> details[i];
    }

    cout << "Número de linhas: " << nRows << ", Número de colunas: " << nCols << endl;
    for (int i = 0; i < 9; ++i) {
        cout << detailNames[i] << ": " << details[i] << endl;
    }

    // Inicializar variáveis da classe Simulador
    Simulador sim;
    sim.instantes_itens = details[1];
    sim.lifetime_itens = details[2];
    sim.max_itens = details[3];
    sim.instantes_barbaros = details[7];
    sim.barbaros_lifetime = details[8];
    sim.setRunning(false);
    sim.setTurnRunning(false);

    // Atualizar a variável estática das moedas
    Caravana::setMoedas(static_cast<float>(details[0]));

    // Inicializar o mapa e sorteio
    sim.mapa_ = new Mapa(nRows, nCols);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            if (char ch = gridLines[i][j]; ch == DESERTO_CHAR) {
                sim(i,j).setTipo(Localizacoes::Deserto);
                sim.mapa_->getBuffer() << DESERTO_CHAR;
            }
            else if (ch == MONTANHA_CHAR) {
                sim(i,j).setTipo(Localizacoes::Montanha);
                sim.mapa_->getBuffer() << MONTANHA_CHAR;
            }
            else if (ch >= 'a' && ch <= 'z') {
                Cidade* cidade = new Cidade(ch, details[4], details[5], details[6]);
                sim(i,j).setCelula(cidade);
                sim.mapa_->getBuffer() << cidade;
            }
            else if (ch >= '0' && ch <= '9') {
                Caravana* caravana;
                if (dis(gen) == 0)
                    caravana = new CaravanaComercio(ch);
                else
                    caravana = new CaravanaMilitar(ch);
                sim(i,j).setCelula(caravana);
                sim.mapa_->getBuffer() << caravana;
            }
            else if (ch == '!') {
                Caravana *carBar = new CaravanaBarbara(ch);
                sim(i,j).setCelula(carBar);
                sim.mapa_->getBuffer() << carBar;
            }
        }
    }

    return sim;
}

void Simulador::run() {
    setRunning(true);
    while (getRunning()) {
        setTurnRunning(true);
        while (getTurnRunning()) {
            readCommand();
        }
    }
}

void Simulador::readCommand() {
    string line;
    cout << "> ";
    getline(cin, line);
    istringstream iss;
    string cmd, c1, c2;
    iss >> cmd;
    Caravana *car;
    Cidade *cid;
    char ch1, ch2;

    if (cmd == "prox") {
        if (int n; iss >> n) {
            for (int i=0; i<n; i++)
                executeInstant();
        }
        else
            executeInstant();

        setTurnRunning(false);
    }
    else if (cmd == "terminar") {
        setRunning(false);
    }
    else if (cmd == "comprac") {
        if (!(iss >> c1 >> c2)) {
            cout << "Erro: Numero insuficiente de parametros\n";
            return;
        }
        ch1 = c1[0];
        ch2 = c2[0];
        cid = Cidade::find(this->getMapa(), ch1);
        if (cid == nullptr) {
            cout << "Erro: Nao foi encontrada a cidade '" << ch1 << "'.\n";
            return;
        }
        cid->compra(ch2);
    }
    else if (cmd == "precos") {

    }
    else if (cmd == "cidade") {
        if (!(iss >> c1)) {
            cout << "Erro: Numero insuficiente de parametros\n";
            return;
        }
        ch1 = c1[0];
        cid = Cidade::find(this->getMapa(), ch1);
        if (cid == nullptr) {
            cout << "Erro: Nao foi encontrada a cidade '" << ch1 << "'.\n";
            return;
        }
        cout << cid->listCaravanas();
    }
    else if (cmd == "caravana") {
        if (!(iss >> c1)) {
            cout << "Erro: Numero insuficiente de parametros\n";
            return;
        }
        ch1 = c1[0];
        car = Caravana::find(this->getMapa(), ch1);
        if (car == nullptr) {
            cout << "Erro: Nao foi encontrada a caravana '" << ch1 << "'.\n";
            return;
        }
        cout << car;
    }
    else if (cmd == "compra") {
        if (!(iss >> c1 >> c2)) {
            cout << "Erro: Numero insuficiente de parametros\n";
            return;
        }
        float amount = stof(c1);
        ch2 = c2[0];
        car = Caravana::find(this->getMapa(), ch2);
        if (car == nullptr) {
            cout << "Erro: Nao foi encontrada a caravana '" << ch2 << "'.\n";
            return;
        }

    }
    else if (cmd == "vende") {

    }
    else if (cmd == "move") {
        if (!(iss >> c1 >> c2)) {
            cout << "Erro: Numero insuficiente de parametros\n";
            return;
        }
        ch1 = c1[0];
        car = Caravana::find(this->getMapa(), ch1);
        if (car == nullptr) {
            cout << "Erro: Nao foi encontrada a caravana '" << ch1 << "'.\n";
            return;
        }
        car->move(this->getMapa(), c2);
    }
    else if (cmd == "auto") {
        if (!(iss >> c1 >> c2)) {
            cout << "Erro: Numero insuficiente de parametros\n";
            return;
        }
        ch1 = c1[0];
        car = Caravana::find(this->getMapa(), ch1);
        if (car == nullptr) {
            cout << "Erro: Nao foi encontrada a caravana '" << ch1 << "'.\n";
            return;
        }
        car->setComportamento(true);
    }
    else if (cmd == "stop") {
        if (!(iss >> c1 >> c2)) {
            cout << "Erro: Numero insuficiente de parametros\n";
            return;
        }
        ch1 = c1[0];
        car = Caravana::find(this->getMapa(), ch1);
        if (car == nullptr) {
            cout << "Erro: Nao foi encontrada a caravana '" << ch1 << "'.\n";
            return;
        }
        car->setComportamento(false);
    }
    else if (cmd == "moedas") {
        if (!(iss >> c1)) {
            cout << "Erro: Numero insuficiente de parametros\n";
            return;
        }
        float amount = stof(c1);
        Caravana::setMoedas(Caravana::getMoedas() + amount);
    }
    else if (cmd == "tripul") {
        if (!(iss >> c1 >> c2)) {
            cout << "Erro: Numero insuficiente de parametros\n";
            return;
        }
    }
    else if (cmd == "saves") {
        if (!(iss >> c1)) {
            cout << "Erro: Numero insuficiente de parametros\n";
            return;
        }
        this->insere_buffer(c1, this->getMapa()->getBuffer());
    }
    else if (cmd == "loads") {
        if (!(iss >> c1)) {
            cout << "Erro: Numero insuficiente de parametros\n";
            return;
        }
        cout << get_buffer(c1);
    }
    else if (cmd == "lists"){
        cout << list_buffers();
    }
    else if (cmd == "dels"){
        if (!(iss >> c1)) {
            cout << "Erro: Numero insuficiente de parametros\n";
            return;
        }
        this->remove_buffer(c1);
    }
    else {
        cout << "Erro: Comando Invalido.\n";
    }

}

void Simulador::executeInstant() {

}

void Simulador::executeTurn() {

}



Mapa *Simulador::getMapa() const {
    return mapa_;
}


std::string Simulador::get_buffer(string nome) {
    ostringstream oss;
    auto it = buffers.find(nome);
    if (it == buffers.end())
        return "Nao encontrado\n";
    oss << it->second.getContent();
    return oss.str();
}

std::string Simulador::list_buffers() const {
    ostringstream oss;
    for (const auto& b: buffers)
        oss <<"- " <<  b.first << ";\n";
    return oss.str();
}

bool Simulador::insere_buffer(const string &nome, const Buffer& buffer) {
    if (buffers.find(nome) != buffers.end())
        return false;
    buffers.insert({nome,buffer});
    return true;
}

bool Simulador::remove_buffer(const string& nome) {
    auto it = buffers.find(nome);
    if (it != buffers.end()) {
        buffers.erase(it);
        return true;
    }
    return false;
}




Celula &Simulador::operator()(int row, int col) const {
    return mapa_->getMapa()[row][col];
}


bool Simulador::getRunning() const {
    return running;
}

void Simulador::setRunning(bool r) {
    running = r;
}

int Simulador::getBarbarosLifetime() const {
    return barbaros_lifetime;
}

int Simulador::getInstantesBarbaros() const {
    return instantes_barbaros;
}

int Simulador::getInstantesItens() const {
    return instantes_itens;
}

int Simulador::getLifetimeItens() const {
    return lifetime_itens;
}

int Simulador::getMaxItens() const {
    return max_itens;
}

bool Simulador::getTurnRunning() const {
    return turnRunning;
}

void Simulador::setTurnRunning(bool tr) {
    turnRunning = tr;
}








