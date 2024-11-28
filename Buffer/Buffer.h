//
// Created by rodrigo on 27-11-2024.
//

#ifndef BUFFER_H
#define BUFFER_H
#include "Cursor.h"
using namespace std;

class Buffer {
public:
    Buffer(int numRows, int numCols);
    ~Buffer();
    string getContent() const;
    void esvazia() const;
    void moveCursor(int nRow, int nCol);
    void put(char c);
    void put(const string& s);
    void put(int i);
    Buffer &operator<<(char ch);
    Buffer &operator<<(int i);
    Buffer &operator<<(const string& s);
private:
    char **mapa;
    const int nRows, nCols;
    Cursor cursor_;
};

ostream &operator<<(ostream &output, const Buffer &b);

#endif //BUFFER_H
