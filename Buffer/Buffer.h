//
// Created by rodrigo on 27-11-2024.
//

#ifndef BUFFER_H
#define BUFFER_H
#include "Cursor.h"
#include "../Localizações/Caravana.h"
#include "../Localizações/Cidade.h"
#include "../Localizações/Item.h"
using namespace std;

class Buffer {
public:
    Buffer(int numRows, int numCols);
    ~Buffer();
    Buffer &operator=(const Buffer &outro);
    Buffer(const Buffer &outro);

    string getContent() const;
    void esvazia() const;
    void moveCursor(int nRow, int nCol);
    void put(char c);
    void put(const string& s);
    void put(int i);

    Buffer &operator<<(char ch);
    Buffer &operator<<(int i);
    Buffer &operator<<(const string& s);

    Buffer &operator<<(const Item *i);
    Buffer &operator<<(const Caravana *car);
    Buffer &operator<<(const Cidade *c);

    Buffer &operator++();
    Buffer &operator()(int row, int col);
    Buffer &operator()();
private:
    char **grid;
    const int nRows, nCols;
    Cursor cursor_;
};

ostream &operator<<(ostream &output, const Buffer &b);

#endif //BUFFER_H
