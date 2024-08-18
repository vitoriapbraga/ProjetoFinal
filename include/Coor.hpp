#ifndef COOR_HPP
#define COOR_HPP

#include <cstring>
// Define a coordenada (row, column)
class coor
{
public:
    int row, col;
    // this struct can be defined with its values initialized
    // if no parameter passed, the default value is 0
    coor(int r = 0, int c = 0) : row(r), col(c) {}
    // equavalent to the above
    /*
    coor(int c = 0, int r = 0)
    {
        col = c.col;
        row = c.row;
    }
    */
    // coor(const coor &c) : col(c.col), row(c.row) {}
    void operator+=(const int dir[2])
    {
        row += dir[0];
        col += dir[1];
    }
};

#endif