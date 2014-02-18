/* 
 * File:   AStar.h
 * Author: annonator
 *
 */

#ifndef ASTAR_H
#define	ASTAR_H

#include <vector>
#include "Node.h"

 using namespace std;

class AStar {
public:
    AStar();
    AStar(const AStar& orig);
    virtual ~AStar();

    void setNodes(vector<Node*>& newNode);
    void setStartEndNode(Node* startNode, Node* endNode);
    void setDestinationNode(Node* destinationNode);
    void solve();
    void solve(Node* start, Node* end);
protected:
	vector<Node*> m_navPoints;
	Node* m_startNode;
	Node* m_endNode;

};

#endif	/* ASTAR_H */

