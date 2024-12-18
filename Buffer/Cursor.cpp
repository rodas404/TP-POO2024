//
// Created by rodrigo on 18-12-2024.
//

#include <iostream>
#include "Cursor.h"

Cursor::Cursor(): row(0), col(0) {
}

int Cursor::getCol() const {
    return col;
}

int Cursor::getRow() const {
    return row;
}

void Cursor::setCol(const int nCol) {
    col = nCol;
}

void Cursor::setRow(const int nRow) {
    row = nRow;
}

void Cursor::moveTo(const int nRow, const int nCol) {
    setCol(nCol);
    setRow(nRow);
}
