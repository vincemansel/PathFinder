//
//  common.h
//  pathfinder
//
//  Created by Vince Mansel on 10/28/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#ifndef pathfinder_common_h
#define pathfinder_common_h

#include "genlib.h"
#include "extgraph.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "vector.h"
#include "set.h"
#include "map.h"
#include "simpio.h"

/* Constants
 * --------
 * A few program-wide constants concerning the graphical display.
 */
const double CircleRadius =.05;     	// the radius of a node
const int LabelFontSize = 9;          // for node name labels


/* Type: coordT
 * ------------
 * Just a simple struct to handle a pair of x,y coordinate values.
 */
struct coordT {
	double x, y;
};

struct nodeT;

struct arcT {
    nodeT *start, *end;
    double distance;
};

struct nodeT {
    string name;
    double x;
    double y;
    Vector<arcT *> links;
};

coordT GetCoords(nodeT *n);


/* Function: DrawLineBetween
 * Usage:  DrawLineBetween(coord1, coord2, "Black");
 * -------------------------------------------------
 * Uses facilities from extgraph to draw a line of the
 * specified color between the two given coordinates.
 */

void DrawLineBetween(coordT start, coordT end, string color);
void DrawFilledCircleWithLabel(coordT center, string color, string label = "");


#endif

