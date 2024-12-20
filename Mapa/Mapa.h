//
// Created by rodrigo on 29-11-2024.
//

#ifndef MAPA_H
#define MAPA_H
#include "Celula.h"
#include "../Buffer/Buffer.h"

class Mapa {
public:
    Mapa(int numRow, int numCols);
    ~Mapa();
    Mapa &operator=(const Mapa &outro);

    const Buffer& getBuffer() const;
    int getRows() const;
    int getCols() const;
    Celula** getMapa() const;

    static Mapa readFile(const string &fileName);
    bool move(Caravana *car, int dx, int dy);

private:
    Celula **mapa;
    int nRows, nCols;
    Buffer buffer_;

};

ostream &operator<<(ostream &output, const Mapa &m);



#endif //MAPA_H
