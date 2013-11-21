#ifndef TILE_H
#define TILE_H
#include <QtGui>
#define S 40

class tile : public QGraphicsRectItem
{
    int row,col,color,posx,posy;
    tile(int x, int y, int c);
    void mousePressEvent(QMouseEvent *event);
};

#endif // TILE_H
