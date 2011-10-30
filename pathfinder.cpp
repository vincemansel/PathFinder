//
//  pathfinder.cpp
//  pathfinder
//
//  Created by Vince Mansel on 10/27/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

/*
 * ---------------
 * From the user's point of view, the program draws a graph
 * and provides two operations: finding the shortest path
 * between two locations and constructing the minimal cost network.
 * The user chooses the graph data file for the program to read and display.
 *
 * This is the main file with some starting constants and handy utility routines.
 */

#include "common.h"
#include "shortestPathFirst.h"
#include "minimumSpanningTree.h"

// Moved to common.h
///* Constants
// * --------
// * A few program-wide constants concerning the graphical display.
// */
//const double CircleRadius =.05;     	// the radius of a node
//const int LabelFontSize = 9;          // for node name labels

// Moved to common.h
///* Type: coordT
// * ------------
// * Just a simple struct to handle a pair of x,y coordinate values.
// */
//struct coordT {
//	double x, y;
//};


// Moved to common.h
///* Function: DrawFilledCircleWithLabel
// * Usage:  DrawFilledCircleWithLabel(center, "Green", "You are here");
// * -------------------------------------------------------------------
// * Uses facilities from extgraph to draw a circle filled with
// * color specified. The circle is centered at the given coord has the
// * specified radius.  A label is drawn to the right of the circle.
// * You can leave off the last argument if no label is desired.
// */
//void DrawFilledCircleWithLabel(coordT center, string color, string label = "")
//{
//	MovePen(center.x + CircleRadius, center.y);
//	SetPenColor(color);
//	StartFilledRegion(1.0);
//	DrawArc(CircleRadius, 0, 360);
//	EndFilledRegion();
//	if (!label.empty()) {
//		MovePen(center.x + CircleRadius, center.y);
//		SetFont("Helvetica");
//		SetPointSize(LabelFontSize);
//		DrawTextString(label);
//	}
//}

// Moved to common.h
///* Function: DrawLineBetween
// * Usage:  DrawLineBetween(coord1, coord2, "Black");
// * -------------------------------------------------
// * Uses facilities from extgraph to draw a line of the
// * specified color between the two given coordinates.
// */
//void DrawLineBetween(coordT start, coordT end, string color)
//{
//	SetPenColor(color);
//	MovePen(start.x, start.y);
//	DrawLine(end.x - start.x, end.y - start.y);
//}


/* Function: GetMouseClick
 * Usage:  loc = GetMouseClick();
 * ------------------------------
 * Waits for the user to click somewhere on the graphics window
 * and returns the coordinate of where the click took place.
 */
coordT GetMouseClick()
{
	coordT where;
	WaitForMouseDown();
	WaitForMouseUp();
	where.x = GetMouseX();
	where.y = GetMouseY();
	return where;
}

/* Function: WithinDistance
 * Usage:  if (WithinDistance(click, pt))...
 * -----------------------------------------
 * Returns true if the Cartesian distance between the two coordinates
 * is <= the specified distance, false otherwise. If not specified,
 * the distance is assumed to be size of the node diameter on screen.
 */
bool WithinDistance(coordT pt1, coordT pt2, double maxDistance = CircleRadius*2)
{
	double dx = pt2.x - pt1.x;
	double dy = pt2.y - pt1.y;
	double distance = sqrt(dx*dx + dy*dy);
	return (distance <= maxDistance);
}

// Moved to common.h
//struct nodeT;
//
//struct arcT {
//    nodeT *start, *end;
//    double distance;
//};
//
//struct nodeT {
//    string name;
//    double x;
//    double y;
//    Vector<arcT *> links;
//};

struct graphT {
    Set<nodeT *> allNodes;
};

string ReadGraph(Set<nodeT *> &graph, Map<nodeT *> &graphMap, string datafile);
void PrintGraphMap(Map<nodeT *> &graphMap);
void PrintGraph(Set<nodeT *> &graph);
void DrawNodesAndArcs(Set<nodeT *> graph);
void HandleShortestPath(Set<nodeT *> &graph);
bool IsCyclicGraph(graphT & graph);

int main()
{
    Set<nodeT *> graph;
    Map<nodeT *> graphMap;
    
	InitGraphics();
	SetWindowTitle("Pathfinder");
    
    string backgroundFile;
    bool timeToQuit = false;
    
    
    cout << "This masterful piece of work is a graph extravaganza!" << endl;
    
    while (true) {
        
        cout << "Your options are:" << endl;
        cout << "(1) Choose a new graph data file" << endl;
        cout << "(2) Find shortest path using Dijkstra's algorithm" << endl;
        cout << "(3) Compute the minimal spanning tree using Kruskal's algorithm" << endl;
        cout << "(4) Determine if the graph has cycles" << endl;
        cout << "(5) Quit" << endl;
        cout << "Enter choice: ";
        
        int choice = GetInteger();
        string datafile;
        void UpdateDisplay();
        
        switch (choice) {
            case 1:
                cout << "Enter the name of the data file: ";
                datafile = GetLine();
                //datafile = "Small.txt";
                //datafile = "USA.txt";
                //datafile = "Stanford.txt";
                graph.clear();
                graphMap.clear();
                backgroundFile = ReadGraph(graph, graphMap, datafile);
                break;
            case 2:
                if (backgroundFile == "") {
                    cout << "No file is specified" << endl;
                }
                else {
                    UpdateDisplay();
                    MovePen(0,0);
                    DrawNamedPicture(backgroundFile);
                    DrawNodesAndArcs(graph);
                    cout << "(2) Finding shortest path using Dijkstra's algorithm" << endl;
                    HandleShortestPath(graph);
                }
                break;
            case 3:
                if (backgroundFile == "") {
                    cout << "No file is specified" << endl;
                }
                else {
                    cout << "(3) Computing the minimal spanning tree using Kruskal's algorithm" << endl;
                    UpdateDisplay();
                    MovePen(0,0);
                    DrawNamedPicture(backgroundFile);
                    //DrawNodesAndArcs(graph);
                    minimumSpanningTree(graph, graphMap);
                }
                break;
            case 4:
                if (backgroundFile == "") {
                    cout << "No file is specified" << endl;
                }
                else {
                    graphT graph2;
                    graph2.allNodes = graph;
                    
                    cout << "(4) Determining if the graph has cycles" << endl;
                    if (IsCyclicGraph(graph2))
                        cout << "Yes, it is cyclic" << endl;
                    else
                        cout << "No, it is not cyclic" << endl;
                }
                break;
            case 5:
                cout << "Thanks for using Pathfinder. Bye!" << endl;
                timeToQuit = true;
                break;
                
            default:
                cout << "Invalid choice" << endl;
                break;
        }
        
        if (timeToQuit) break;
        
    }
    return (0);
}

// Reads the graph file and returns the background file string

string ReadGraph(Set<nodeT *> &graph, Map<nodeT *> &graphMap, string datafile) {
    
    ifstream inner;
    inner.open(datafile.c_str());
    if (inner.fail()) Error("Can't open file");
    
    string background;
    inner >> background;
    string name;
    inner >> name;
    
    //cout << "Background file: " << background << endl;
    //cout << name << endl;
    
    while (true) {
        nodeT *n = new nodeT;
        if (inner.fail()) break; // no more lines to read
        //double x, y;
        inner >> n->name;
        if (n->name == "ARCS")
            break;
        else
            inner >> n->x >> n->y;
        
        graphMap.add(n->name,n);
        graph.add(n);
        
        //cout << n->name << " " << n->x << ":" << n->y << endl;
        
    }
    
    //    cout << endl << endl;
    //    cout << "THE GRAPH MAP" << endl;
    //    cout << endl;
    //    PrintGraphMap(graphMap);
    
    while (true) {
        if (inner.fail()) break; // no more lines to read
        string name1, name2;
        double distance;
        inner >> name1 >> name2 >> distance;
        if (name1 == "") break;
        //cout << name1 << " <-> " << name2 << " :" << distance << endl;
        
        arcT *arc1 = new arcT;
        arcT *arc2 = new arcT;
        
        arc1->start = graphMap.get(name1);
        arc1->end = graphMap.get(name2);
        arc1->distance = distance;
        
        arc2->end = graphMap.get(name1);
        arc2->start = graphMap.get(name2);
        arc2->distance = distance;
        
        nodeT *node1 = graphMap.get(name1);
        nodeT *node2 = graphMap.get(name2);
        
        node1->links.add(arc1);
        node2->links.add(arc2);
    }
    
    inner.close();
    
    //    cout << endl << endl;
    //    cout << "THE GRAPH" << endl;
    //    PrintGraphMap(graphMap);
    //    PrintGraph(graph);
    
    MovePen(0,0);
    DrawNamedPicture(background);
    DrawNodesAndArcs(graph);
    
    return background;
}

void PrintGraphMap(Map<nodeT *> &graphMap) {
    Map<nodeT *>::Iterator itr = graphMap.iterator();
    
    while (itr.hasNext()) {
        string city = itr.next();
        nodeT *n = graphMap.get(city);
        cout << n->name << ":" << n->x << ":" << n->y << endl;
    }
}

void PrintGraph(Set<nodeT *> &graph) {
    cout << endl;
    cout << endl;
    Set<nodeT *>::Iterator itr = graph.iterator();
    
    while (itr.hasNext()) {
        nodeT *n = itr.next();
        cout << n->name << ":" << n->x << ":" << n->y << endl;
        cout << "ARCS:" << endl;
        
        Vector<arcT *>::Iterator itrArc = n->links.iterator();
        
        while (itrArc.hasNext()) {
            arcT *arc = itrArc.next();
            cout << arc->distance << ":" << arc->start->name << ":"
            << arc->end->name << endl;
        }
        cout << endl;
    }
}

void DrawNodesAndArcs(Set<nodeT *> graph) {
    Set<nodeT *>::Iterator itr = graph.iterator();
    
    while (itr.hasNext()) {
        nodeT *n = itr.next();
        
        coordT center = GetCoords(n);
        DrawFilledCircleWithLabel(center, "Black", n->name);
        
        Vector<arcT *>::Iterator itrArc = n->links.iterator();
        
        while (itrArc.hasNext()) {
            arcT *arc = itrArc.next();
            DrawLineBetween(GetCoords(arc->start), GetCoords(arc->end), "Black");
        }
    }
}

nodeT * GetPoint(Set<nodeT *> graph, string message, string color) {
    
    nodeT *node;
    while (true) {
        cout << message << endl;
        coordT point1 = GetMouseClick();
        bool pointFound = false;
        Set<nodeT *>::Iterator itr = graph.iterator();
        while (itr.hasNext()) {  // Test if click was close enough to a known location
            node = itr.next();
            if (WithinDistance(GetCoords(node),point1)) {
                cout << node->name << endl;
                DrawFilledCircleWithLabel(GetCoords(node), color);
                pointFound = true;
                break;
            }
        }
        if (pointFound)
            break;
        else
            cout << "Try Again" << endl;
    }
    
    return node;
}

void HandleShortestPath(Set<nodeT *> &graph) {
    
    nodeT *node1 = GetPoint(graph, "Click on the starting point in the Map", "Green");
    nodeT *node2 = GetPoint(graph, "Click on the ending point in the Map", "Red");
    
    ShortestPathFirst(node1, node2);
}

bool RecIsCyclic(nodeT * currentNode, nodeT * targetNode, int hops, Set<nodeT *> &visited) {
    
    if (hops > 2 && currentNode == targetNode)
        return true;
    
    if (currentNode != targetNode)
        visited.add(currentNode);
    
    Vector<arcT *>::Iterator itr = currentNode->links.iterator();
    
    while (itr.hasNext()) {
        arcT * link = itr.next();
        cout << " Link is (" << hops+1 << ") : " << link->end->name << endl;
        if (!visited.contains(link->end) && !(hops+1 < 3 && link->end == targetNode)) {
            cout << " Checking: " << link->end->name << endl;
            if (RecIsCyclic(link->end, targetNode, hops+1, visited))
                return true;
        }
    }
    return false;
}

bool IsCyclicGraph(graphT & graph) {
    
    Set<nodeT *>::Iterator itr = graph.allNodes.iterator();
    
    while (itr.hasNext()) {
        nodeT * currentNode = itr.next();
        Set<nodeT *> visited;
        cout << "Node is: " << currentNode->name << endl;
        if (RecIsCyclic(currentNode, currentNode, 0, visited))
            return true;
    }
    return false;
}
