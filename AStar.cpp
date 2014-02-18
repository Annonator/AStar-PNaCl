/* 
 * File:   AStar.cpp
 * Author: annonator
 * 
 */

#include "AStar.h"

AStar::AStar() {
}

AStar::AStar(const AStar& orig) {
}

AStar::~AStar() {
    delete m_startNode;
}

void AStar::setNodes(vector<Node*>& newNode){
    m_navPoints = newNode;
}

void AStar::setStartEndNode(Node* startNode, Node* endNode){
    m_startNode = startNode;
    m_endNode = endNode;
}

void AStar::setDestinationNode(Node* destinationNode){
    Node::setDestinationNode(destinationNode);
}

void AStar::solve(){
	//Clear
	int count = m_navPoints.size();
	for(int i = 0; i < count; ++i){
		m_navPoints[i]->reset(false);
	}

	//Initialisiere start knoten
	m_startNode->reset(true);

	vector<Node*> frontier;
	frontier.push_back(m_startNode);

	//Lösung
	while((!m_endNode->isSolution() && (!frontier.empty()))){
		count = frontier.size();
		int candidate = 0;
		float value = frontier[0]->getWeight();
		for(int i = 1; i < count; ++i){
			//suche besseren Wert
			float localValue = frontier[i]->getWeight();
			if(localValue < value){
				//Bessere Wert gefunden
				candidate = i;
				value = localValue;
			}
		}

		Node* nextNode = frontier[candidate];
		//entferne zu erweiterten knoten
		frontier[candidate] = frontier[count - 1];
		frontier.pop_back();
		//expandiere knoten
		nextNode->setActiveNode(frontier);

		if(nextNode == m_endNode){
			m_endNode->processBackwards();
		}
	}
}

void AStar::solve(Node* start, Node* end){
	setStartEndNode(start, end);
	Node::setDestinationNode(end);
	solve();
}
