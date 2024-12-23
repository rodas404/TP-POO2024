//
// Created by rodrigo on 27-11-2024.
//
#include <iostream>
#include <string>
#include <sstream>
#include "Buffer.h"


Buffer::Buffer(const int numRows, const int numCols): nRows(numRows), nCols(numCols) {
    grid = new char *[nRows];
    for (int i=0; i< nRows; i++) {
        grid[i] = new char[nCols];
    }
    esvazia();
}

void Buffer::esvazia() const {
    for (int i=0; i<nRows; i++) {
        for (int j=0; j<nCols; j++) {
            grid[i][j] = ' ';
        }
    }
}

Buffer::~Buffer() {
    for (int i=0; i<nRows; i++)
        delete[] grid[i];

    delete[] grid;
}

string Buffer::getContent() const {
    ostringstream oss;
    oss << "Mapa atual:\n";
    for (int i=0; i<nRows; i++) {
        for (int j=0; j<nCols; j++) {
            oss << grid[i][j];
            if (j < nCols -1)
                oss << " ";
        }
        oss << "\n";
    }
    return oss.str();
}

void Buffer::moveCursor(int nRow, int nCol) {
    if (nCol >= nCols) {
        nCol = 0;
        nRow++;
    }
    else if (nCol < 0) {
        nCol = nCols - 1;
        nRow--;
    }

    if (nRow >= nRows)
        nRow = 0;

    else if (nRow < 0)
        nRow = nRows - 1;

    cursor_.moveTo(nRow, nCol);
}

void Buffer::put(const char c){
    grid[cursor_.getRow()][cursor_.getCol()] = c;
    ++(*this);
}

void Buffer::put(const int i) {
    grid[cursor_.getRow()][cursor_.getCol()] = static_cast<char>(i + '0');;
    ++(*this);
}



void Buffer::put(const string& s) {
    for (const char ch: s)
        put(ch);
}


Buffer &Buffer::operator<<(const Caravana *car) {
    put(car->getId());
    return *this;
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

Buffer &Buffer::operator<<(const Cidade *c) {
    put(c->getId());
    return *this;
}


Buffer &Buffer::operator<<(const Item *) {
    put('?');
    return *this;
}

Buffer &Buffer::operator++() {
    moveCursor(cursor_.getRow(), cursor_.getCol() + 1);
    return *this;
}

Buffer &Buffer::operator()(const int row, const int col) {
    moveCursor(row, col);
    return *this;
}


Buffer &Buffer::operator()() {
    esvazia();
    return *this;
}

Buffer& Buffer::operator=(const Buffer &outro) {
    if (this == &outro) 
        return *this; 

    //apaga original
    for (int i = 0; i < nRows; ++i) 
        delete[] grid[i];
    delete[] grid;

    //cria e atribui
    grid = new char*[nRows];
    for (int i = 0; i < nRows; ++i) {
        grid[i] = new char[nCols];
        for (int j = 0; j < nCols; ++j) 
            grid[i][j] = outro.grid[i][j];
    }

    return *this;
}

Buffer::Buffer(const Buffer &outro): nRows(outro.nRows), nCols(outro.nCols) {
    grid = new char*[nRows];
    for (int i = 0; i < nRows; ++i) {
        grid[i] = new char[nCols];
        for (int j = 0; j < nCols; ++j)
            grid[i][j] = outro.grid[i][j];
    }
    esvazia();
}





