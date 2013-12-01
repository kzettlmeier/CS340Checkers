/**
 *  \file tile.cpp
 *  Contains the actions for the UI events
 *
 *  This creates the tiles that populate the grid and create a graphical representation
 *  of the checker board. This depicts the same game logic and moves that are calculated
 *  in the other files, but shows a visual representation of casting a player's move and
 *  moving the piece to a new valid location on the board.
 *
 *  \author Andrew Guillen
 *  \author Shane Lopez
 *  \author Kendall Zettlmeier
 *  \version 1.0
 *  \date December 2013
 *  \bug No major bugs were found upon testing
 *
 */

#include "tile.h"

/**
 * @brief tile::tile
 *  creates the tiles for the grid
 * @param x
 * @param y
 * @param c
 */
tile::tile(int x, int y, int c) {
    row = y;
    col = x;
    color = c;
    posx = y + S/4;
    posy = x + S/4;
}
void tile::mousePressEvent(QMouseEvent *event) {






}
