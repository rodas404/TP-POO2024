//
// Created by rodrigo on 27-11-2024.
//
#include <iostream>
#include <string>
#include <sstream>
#include "Buffer.h"


Buffer::Buffer(int numRows, int numCols): nRows(numRows), nCols(numCols) {
    mapa = new char *[nRows];
    for (int i=0; i< nRows; i++) {
        mapa[i] = new char[nCols];
    }
    esvazia();
}

void Buffer::esvazia() const {
    for (int i=0; i<nRows; i++) {
        for (int j=0; j<nCols; j++) {
            mapa[i][j] = '.';
        }
    }
}

Buffer::~Buffer() {
    for (int i=0; i<nRows; i++)
        delete[] mapa[i];

    delete[] mapa;
}

string Buffer::getContent() const {
    ostringstream oss;
    oss << "Mapa atual:\n";
    for (int i=0; i<nRows; i++) {
        for (int j=0; j<nCols; j++) {
            oss << mapa[i][j];
            if (j < nCols -1)
                oss << " ";
        }
        oss << "\n";
    }
    return oss.str();
}

void Buffer::moveCursor(int nRow, int nCol) {
    if (nRow >= nRows)
        nRow = 0;
    else if (nRow < 0)
        nRow = nRows - 1;

    if (nCol >= nCols)
        nCol = 0;
    else if (nCol < 0)
        nCol = nCols - 1;

    cursor_.moveTo(nRow, nCol);
}

void Buffer::put(const char c){
    mapa[cursor_.getRow()][cursor_.getCol()] = c;
    moveCursor(cursor_.getRow(), cursor_.getCol()+1);
}

void Buffer::put(const int i) {
    mapa[cursor_.getRow()][cursor_.getCol()] = static_cast<char>(i + '0');;
    moveCursor(cursor_.getRow(), cursor_.getCol()+1);
}

void Buffer::put(const string& s) {
    for (const char ch: s)
        put(ch);
}

ostream &operator<<(ostream &output, const Buffer &b) {
    output << b.getContent();
    return output;
}

Buffer& Buffer::operator<<(const char ch) {
    put(ch);
    return *this;
}

Buffer &Buffer::operator<<(const int i) {
    put(i);
    return *this;
}

Buffer &Buffer::operator<<(const string& s) {
    put(s);
    return *this;
}







