//
// Created by rodrigo on 29-11-2024.
//
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include "Mapa.h"

#include "../Caravanas/CaravanaComercio.h"

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



const Buffer &Mapa::getBuffer() const {
    return buffer_;
}
ostream &operator<<(ostream &output, const Mapa &m) {
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
            char ch = gridLines[i][j];
            if (ch == '.') {
                mapa.mapa[i][j].setTipo(Localizacoes::Deserto);
                mapa.buffer_ << '.';
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
                Caravana* caravana = new CaravanaComercio(ch, details[0]);
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

void Mapa::move(int x, int y, int dx, int dy) {
    if (dy>= nCols)
        dy = 0;
    else if (dy < 0)
        dy = nCols - 1;

    if (dx >= nRows)
        dx = 0;

    else if (dx < 0)
        dx = nRows - 1;

    if (mapa[dx][dy].getTipo() == Localizacoes::Cidade) {
        cout << "movi para cidade";
        mapa[dx][dy].getCidade()->chegou_caravana(mapa[x][y].getCaravana());
        mapa[x][y].resetCaravana();
        mapa[x][y].setCelula();
        buffer_(x,y) << '.';
    }
    else if (mapa[x][y].getTipo() == Localizacoes::Caravana){
        mapa[dx][dy].setCelula(mapa[x][y].getCaravana());
        mapa[x][y].resetCaravana();
        mapa[x][y].setCelula();
        buffer_(dx,dy) << mapa[dx][dy].getCaravana();
        buffer_(x,y) << '.';
        }

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

