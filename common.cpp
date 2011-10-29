//
//  common.cpp
//  pathfinder
//
//  Created by Vince Mansel on 10/28/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "common.h"

coordT GetCoords(nodeT *n) {
    coordT center;
    center.x = n->x;
    center.y = n->y;
    return center;
}

/* Function: DrawLineBetween
 * Usage:  DrawLineBetween(coord1, coord2, "Black");
 * -------------------------------------------------
 * Uses facilities from extgraph to draw a line of the
 * specified color between the two given coordinates.
 */

void DrawLineBetween(coordT start, coordT end, string color)
{
	SetPenColor(color);
	MovePen(start.x, start.y);
	DrawLine(end.x - start.x, end.y - start.y);
}
