//
//  shortestPathFirst.h
//  pathfinder
//
//  Created by Vince Mansel on 10/28/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#ifndef pathfinder_shortestPathFirst_h
#define pathfinder_shortestPathFirst_h

#include "genlib.h"
#include "common.h"
#include "pqueueT.h"

void ShortestPathFirst(Set<nodeT *> &graph,
                       Map<nodeT *> &graphMap, nodeT *node1, nodeT *node2);

#endif
