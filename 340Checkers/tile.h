/**
 *  \file tile.h
 *  Tile header file
 *
 *  This header file contains the objects that are used by the tile.cpp file
 *  that display the spots on the board.
 *
 *  \author Andrew Guillen
 *  \author Shane Lopez
 *  \author Kendall Zettlmeier
 *  \version 1.0
 *  \date December 2013
 *  \bug No major bugs were found upon testing
 *
 *  \typedef TILE_H An include guard
 *  \def TILE_H defines the tile objects
 *  \def S defines the size of the square tiles to be 40 pixels
 */

#ifndef TILE_H
#define TILE_H
#include <QtGui>
#include <QGraphicsRectItem>
#define S 40

/**
 * @brief The tile class
 *  \var row coordinate for the row (for a move)
 *  \var col coordinate for the column (for a move)
 *  \var color for the tile
 *  \var posx x position for the tile
 *  \var posy y position for the tile
 *
 *  \fn tile a function to draw a tile
 *  \param x x coordinate
 *  \param y y coordinate
 *  \param c color for tile/piece
 */
class tile : public QGraphicsRectItem
{
    int row,col,color,posx,posy;
    tile(int x, int y, int c);
    void mousePressEvent(QMouseEvent *event);
};

#endif // TILE_H
