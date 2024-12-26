//
// Created by rodrigo on 29-11-2024.
//

#ifndef MAPA_H
#define MAPA_H
#include "Celula.h"
#include "../Buffer/Buffer.h"
constexpr char DESERTO_CHAR = '.';
constexpr char MONTANHA_CHAR = '+';

class Mapa {
public:
    Mapa(int numRow, int numCols);
    ~Mapa();
    Mapa &operator=(const Mapa &outro);

    Buffer &getBuffer();
    int getRows() const;
    int getCols() const;
    Celula** getMapa() const;
    std::string getDescricao(int row, int col) const;

    static Mapa readFile(const string &fileName);
    bool move(Caravana *car, int drow, int dcol);
    bool elimina(const Caravana *car);
    bool elimina(const Item *item);
    bool elimina(int row, int col);
    void combates();
    int combate(Caravana* carBar, Caravana* car);
    void spawnItem();
    bool tempestade(int row, int col, int r) const;
    bool spawnBarbaro(int row, int col);
    void spawnBarbaro();

    std::string operator()(int row, int col) const;

private:
    Celula **mapa;
    int nRows, nCols;
    Buffer buffer_;

};

ostream &operator<<(ostream &output, Mapa &m);



#endif //MAPA_H
