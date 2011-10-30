//
//  shortestPathFirst.cpp
//  pathfinder
//
//  Created by Vince Mansel on 10/28/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#include "shortestPathFirst.h"

typedef Stack<nodeT *>  PathStackT;
typedef PQueueT<PathStackT> PathKeeperT;

bool IsSame(nodeT * goal, nodeT * current);
Vector<nodeT *> GetNeighbors(nodeT * current);
bool isAccessible(nodeT * neighbor, nodeT * previous);
double GetPathDistance(PathStackT path, bool doPrint);

void MarkPath(PathStackT path) {
    //cout << "Current Path: distance = " << GetPathDistance(path, true) << endl;
    nodeT * node1 = path.pop();
    while (!path.isEmpty()) {
        nodeT * node2 = path.pop();
        //cout << node1->name << endl;
        DrawLineBetween(GetCoords(node1), GetCoords(node2), "Green");
        node1 = node2;
    }
}

double GetArcDistance(nodeT * &nextNode, string current) {
    Vector<arcT *>::Iterator itr = nextNode->links.iterator();
    while (itr.hasNext()) {
        arcT * link = itr.next();
        if (link->end->name == current)
            return link->distance;
    }
    Error("GetArcDistance: Link not found: " + current + " <-> " + nextNode->name + "." );
    return -1;
}

double GetPathDistance(PathStackT path, bool doPrint) {
    double distance = 0;
    string current = path.pop()->name;
    while (path.size() > 0) {
        nodeT *nextNode = path.pop();
        double arcDistance = GetArcDistance(nextNode,current);
        if (doPrint)
            cout << current << "<->" << nextNode->name << ":" << arcDistance << endl;
        distance += arcDistance;
        current = nextNode->name;
    }
    return distance;
}

int CompareShortestPath(PathStackT path1, PathStackT path2) {
    double one = GetPathDistance(path1, false);
    double two = GetPathDistance(path2, false);
    if (one == two) return 0;
	if (one > two) return -1;
	return 1; // ShortestPath
}

void ShortestPathFirst(nodeT *node1, nodeT *node2) {
    
    //cout << "SPF: IN" << endl;
    
    PQueueT<PathStackT> qStore(CompareShortestPath);
    PathStackT paths;
    Set<nodeT *> visited;
    
    nodeT * current = node1;
    nodeT * goal = node2;
    
    paths.push(current);
    qStore.enqueue(paths);
    
    PathStackT currentPath;
    
    while (true) {
        if (qStore.isEmpty()) {
            cout << "Store is Empty" << endl;
            cout << "Previous current path:" << endl;

            break;
        }
        PathStackT path = qStore.dequeue();
        currentPath = path;
        current = path.pop();
        
        if (IsSame(goal, current)) {
            //cout << "Reached Goal" << endl;
            MarkPath(currentPath);
            break;
        }
        
        if (!visited.contains(current)) {
            visited.add(current);
            for (int i = 0; i < current->links.size(); i++) {
                nodeT * neighbor = current->links[i]->end;
                PathStackT newPath = currentPath;
                newPath.push(neighbor);
                qStore.enqueue(newPath);
            }
        }
    }    
    //cout << "SPF: OUT" << endl;
}

bool IsSame(nodeT * goal, nodeT * current) {
    bool result = false;
    
    if (goal->x == current->x && goal->y == current->y) {
        result = true;
    }
    return result;
}



