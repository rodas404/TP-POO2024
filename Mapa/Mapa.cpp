//
// Created by rodrigo on 29-11-2024.
//
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <random>
#include "Mapa.h"

#include "../Caravanas/CaravanaComercio.h"
#include "../Itens/Jaula.h"
#include "../Itens/Mina.h"
#include "../Itens/ArcaTesouro.h"
#include "../Itens/CaixaPandora.h"
#include "../Itens/PacoteSuspenso.h"
#include "../Caravanas/CaravanaBarbara.h"

Mapa::Mapa(int numRows, int numCols): nRows(numRows), nCols(numCols), buffer_(numRows,numCols) {
    mapa = new Celula *[nRows];
    for (int i=0; i<nRows; i++) {
        mapa[i] = new Celula[nCols];
    }
}

Mapa::~Mapa() {
    for (int i=0; i<nRows;i++) {
        delete[] mapa[i];
    }
    delete[] mapa;
}


Buffer &Mapa::getBuffer() {
    return buffer_;
}


ostream &operator<<(ostream &output, Mapa& m) {
    output << m.getBuffer();
    return output;
}



Mapa Mapa::readFile(const string &fileName) {
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
    vector<int> details(9);
    vector<string> detailNames = {
        "moedas", "instantes_entre_novos_itens", "duração_item", "max_itens",
        "preço_venda_mercadoria", "preço_compra_mercadoria", "preço_caravana",
        "instantes_entre_novos_barbaros", "duração_barbaros"
    };

    for (int & detail : details) {
        getline(file, line);
        istringstream iss(line);
        iss >> temp >> detail;
    }

    cout << "Número de linhas: " << nRows << ", Número de colunas: " << nCols << endl;
    for (int i = 0; i < details.size(); ++i) {
        cout << detailNames[i] << ": " << details[i] << endl;
    }

    Mapa mapa(nRows, nCols);
    // configurar mapa
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            if (char ch = gridLines[i][j]; ch == '.') {
                mapa.mapa[i][j].setTipo(Localizacoes::Deserto);
                mapa.buffer_ << DESERTO_CHAR;
            }
            else if (ch == '+') {
                mapa.mapa[i][j].setTipo(Localizacoes::Montanha);
                mapa.buffer_ << '+';
            }
            else if (ch >= 'a' && ch <= 'z') {
                Cidade* cidade = new Cidade(ch, details[4], details[5], details[6]);
                mapa.mapa[i][j].setCelula(cidade);
                mapa.buffer_ << cidade;
            }
            else if (ch >= '0' && ch <= '9' || ch == '!') {
                Caravana* caravana = new CaravanaComercio(ch);
                mapa.mapa[i][j].setCelula(caravana);
                mapa.buffer_ << caravana;
            }
        }
    }

    return mapa;
}

Mapa& Mapa::operator=(const Mapa& outro) {
    if (this == &outro)
        return *this;

    // apaga original
    for (int i = 0; i < nRows; ++i) {
        delete[] mapa[i];
    }
    delete[] mapa;

    // atribui ao novo
    nRows = outro.nRows;
    nCols = outro.nCols;
    buffer_ = outro.buffer_;

    mapa = new Celula*[nRows];
    for (int i = 0; i < nRows; ++i) {
        mapa[i] = new Celula[nCols];
        for (int j = 0; j < nCols; ++j) {
            mapa[i][j] = outro.mapa[i][j];
        }
    }

    return *this;
}

bool Mapa::move(Caravana *car, int drow, int dcol) {
    auto[row, col] = car->getCoordenadas(this);
    if (row == -1 && col == -1) // não encontrou caravana
        return false;

    // corrigir as coordenadas (o mapa é circular)
    if (drow >= nRows)
        drow = drow % nRows;
    else if (drow < 0)
        drow = nRows + (drow % nRows);

    if (dcol >= nCols)
        dcol = dcol % nCols;
    else if (dcol < 0)
        dcol = nCols + (dcol % nCols);

    if (mapa[drow][dcol].getTipo() != Localizacoes::Deserto && mapa[drow][dcol].getTipo() != Localizacoes::Cidade) // verifica primeiro se move em condições, meter função fixe para acidentes
        return false;

    if (mapa[row][col].getTipo() == Localizacoes::Cidade) { // sai de uma cidade
        if (mapa[row][col].getCidade()->sai_caravana(car->getId())) {
            mapa[drow][dcol].setCelula(car);
            buffer_(drow, dcol) << car;
        }
    } else if (mapa[drow][dcol].getTipo() == Localizacoes::Cidade) { // vai para uma cidade
        mapa[drow][dcol].getCidade()->chegou_caravana(car);
        car->setAgua(car->getMaxAgua());
        mapa[row][col].resetCaravana();
        mapa[row][col].setCelula();
        buffer_(row, col) << DESERTO_CHAR;
    } else if (mapa[drow][dcol].getTipo() == Localizacoes::Deserto) { // condição geral
        mapa[drow][dcol].setCelula(car);
        mapa[row][col].resetCaravana();
        mapa[row][col].setCelula();
        buffer_(drow, dcol) << car;
        buffer_(row, col) << DESERTO_CHAR;
    }

    //apanhar itens
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            int adjRow = (drow + dr + nRows) % nRows;
            int adjCol = (dcol + dc + nCols) % nCols;
            if (mapa[adjRow][adjCol].getItem() != nullptr) {
                mapa[adjRow][adjCol].getItem()->action(car);
                elimina(adjRow,adjCol);
            }
        }
    }

    return true;
}

bool Mapa::elimina(const int row, const int col) {
    if (mapa[row][col].getItem() != nullptr) {
        delete mapa[row][col].getItem();
        mapa[row][col].setCelula();
        buffer_(row,col) << DESERTO_CHAR;
        return true;
    }
    if (mapa[row][col].getCaravana() != nullptr) {
        delete mapa[row][col].getCaravana();
        mapa[row][col].setCelula();
        buffer_(row,col) << DESERTO_CHAR;
        return true;
    }
    return false;
}


int Mapa::getRows() const {
    return nRows;
}

int Mapa::getCols() const {
    return nCols;
}

Celula **Mapa::getMapa() const {
    return mapa;
}


bool Mapa::elimina(const Caravana *car) {
    auto [row,col] = car->getCoordenadas(this);
    if (row == -1 && col == -1)
        return false;

    mapa[row][col].resetCaravana();
    mapa[row][col].setCelula();
    buffer_(row,col) << DESERTO_CHAR;

    delete car;
    return true;
}

void Mapa::combates() {
    for (int row = 0; row < this->getRows(); ++row) { //percorrer mapa
        for (int col = 0; col < this->getCols(); ++col) {
            if (mapa[row][col].getTipo() == Localizacoes::Caravana) {
                Caravana* carBar = mapa[row][col].getCaravana();
                if (carBar && carBar->getTipo() == Tipos::Barbara) { //encontrou caravana barbara
                    for (int i = -1; i<1; ++i) {
                        for (int j=-1; j<1; ++j) { // percorrer adjacencias
                            int newRow = (row + i + nRows) % nRows;
                            int newCol = (col + j + nCols) % nCols;
                            Caravana* car = mapa[newRow][newCol].getCaravana();
                            if (car && car->getTipo() != Tipos::Barbara) //encontrou caravana do utilizador, hora do combate
                                combate(carBar, car);
                        }
                    }
                }
            }
        }
    }
}


int Mapa::combate(Caravana *carBar, Caravana *car) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disBar(0, carBar->getTripulantes());
    std::uniform_int_distribution<> disCar(0, car->getTripulantes());

    int numBar = disBar(gen);
    int numCar = disCar(gen);

    Caravana* vencedora = (numBar > numCar) ? carBar : car;
    Caravana* perdedora = (numBar > numCar) ? car : carBar;

    int perda_vencedora = static_cast<int>(vencedora->getTripulantes() * 0.2);
    int perda_perdedora = perda_vencedora * 2;

    vencedora->setTripulantes(vencedora->getTripulantes() - perda_vencedora);
    perdedora->setTripulantes(perdedora->getTripulantes() - perda_perdedora);

    if (perdedora->getTripulantes() <= 0) {
        vencedora->setAgua(min(vencedora->getAgua() + perdedora->getAgua(), vencedora->getMaxAgua()));
        elimina(perdedora);
    }
    if (vencedora->getTripulantes() <= 0)
        elimina(vencedora);

    return (vencedora == car) ? 1 : 0;
}


void Mapa::spawnItem() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disRow(0, nRows - 1);
    std::uniform_int_distribution<> disCol(0, nCols - 1);
    std::uniform_int_distribution<> disItem(1, 5);

    int row, col;
    do {
        row = disRow(gen);
        col = disCol(gen);
    } while (mapa[row][col].getTipo() != Localizacoes::Deserto);

    Item* item = nullptr;
    switch (disItem(gen)) {
        case 1: item = new ArcaTesouro();
                break;
        case 2: item = new Jaula();
                break;
        case 3: item = new PacoteSuspenso();
                break;
        case 4: item = new Mina();
                break;
        case 5: item = new CaixaPandora();
                break;
        default: return;
    }

    mapa[row][col].setCelula(item);
    buffer_(row, col) << item;
}

bool Mapa::elimina(const Item *item) {
    auto[row,col] = item->getCoordenadas(this);
    if (row == -1 && col == -1)
        return false;

    mapa[row][col].resetItem();
    mapa[row][col].setCelula();
    buffer_(row,col) << DESERTO_CHAR;

    delete item;
    return true;

}


bool Mapa::tempestade(const int row, const int col, const int r) const {
    if (row < 0 || row >= nRows || col < 0 || col >= nCols)
        return false;

    for (int i = -r; i <= r; ++i) {
        for (int j = -r; j <= r; ++j) {
            int newRow = (row + i + nRows) % nRows;
            int newCol = (col + j + nCols) % nCols;

            if (mapa[newRow][newCol].getTipo() == Localizacoes::Caravana) {
                if (Caravana* caravana = mapa[newRow][newCol].getCaravana())
                    caravana->efeitoTempestade();
            }
        }
    }

    return true;
}


bool Mapa::spawnBarbaro(const int row, const int col) {
    if (mapa[row][col].getTipo() != Localizacoes::Deserto)
        return false;

    Caravana* barbaro = new CaravanaBarbara();
    mapa[row][col].setCelula(barbaro);
    buffer_(row, col) << barbaro;
    return true;
}


std::string Mapa::getDescricao(const int row, const int col) const {
    if (row < 0 || row >= nRows || col < 0 || col >= nCols)
        return "Coordenadas invalidas.";

    ostringstream oss;
    oss << "Coordenadas: (" << row << ", " << col << ")\n- ";
    oss << mapa[row][col].getDescricao();
    return oss.str();
}


std::string Mapa::operator()(const int row, const int col) const {
    ostringstream oss;
    oss << this->getDescricao(row, col);
    return oss.str();
}


void Mapa::spawnBarbaro() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disRow(0, nRows - 1);
    std::uniform_int_distribution<> disCol(0, nCols - 1);

    int row, col;
    do {
        row = disRow(gen);
        col = disCol(gen);
    } while (mapa[row][col].getTipo() != Localizacoes::Deserto);

    Caravana* barbaro = new CaravanaBarbara();
    mapa[row][col].setCelula(barbaro);
    buffer_(row, col) << barbaro;
}
