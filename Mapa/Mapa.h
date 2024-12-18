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
    const Buffer& getBuffer() const;
    static Mapa readFile(const string &fileName);
    Mapa &operator=(const Mapa &outro);

    void move(int x, int y, int dx, int dy);

private:
    Celula **mapa;
    int nRows, nCols;
    Buffer buffer_;

};

ostream &operator<<(ostream &output, const Mapa &m);



#endif //MAPA_H
