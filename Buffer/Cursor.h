//
// Created by rodrigo on 27-11-2024.
//

#ifndef CURSOR_H
#define CURSOR_H



class Cursor {
public:
    Cursor();
    int getRow() const;
    int getCol() const;
    void setRow(int nRow);
    void setCol(int nCol);
    void moveTo(int nRow, int nCol);
private:
    int row, col;
};



#endif //CURSOR_H
