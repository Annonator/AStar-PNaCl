/* 
 * File:   Node.cpp
 * Author: annonator
 * 
 */

#include "Node.h"
#include <sstream>

Node* Node::m_destinationNode = NULL;

Node::Node() {
    int x = 0;
    int y = 0;
    
    init(x, y);
}

Node::Node(float x, float y) {
    init(x, y);
}

void Node::init(float x, float y) {
    m_coordinates[0] = x;
    m_coordinates[1] = y;
    //Reset Node im Status INITIAL
    reset(false);
}

Node* Node::getRoot(){
    return m_rootNode;
}

Node::Node(const Node& orig) {
}

Node::~Node() {
    delete m_rootNode;
}

void Node::setDestinationNode(Node* destination) {
    Node::m_destinationNode = destination;
}

void Node::connectWith(Node* otherNode) {
    Link newNode;
    newNode.linkedNode = otherNode;
    newNode.distance = computeDistanceTo(otherNode);
    m_connectedNodes.push_back(newNode);

    //anders rum
    newNode.linkedNode = this;
    otherNode->m_connectedNodes.push_back(newNode);
}

void Node::reset(bool isStartNode) {
    m_upToDistance = 0;
    m_value = 0;
    m_rootNode = NULL;

    if (isStartNode) {
        m_internalState = Node::VISITED;
    } else {
        m_internalState = Node::INITIAL;
    }
}

void Node::resetConnections(){
    m_connectedNodes.clear();
}

void Node::setActiveNode(vector<Node*>& processingList) {
    m_internalState = Node::CLOSED;

    int count = m_connectedNodes.size();

    for (int i = 0; i < count; ++i) {
        Node* connected = m_connectedNodes[i].linkedNode;
        float distance = m_connectedNodes[i].distance;
        if (connected->m_internalState == Node::INITIAL) {
            //Bestimme Kosten bis zum Punkt
            connected->m_upToDistance = m_upToDistance + distance;
            //Bestimme Wert mit Heuristik
            connected->m_value = connected->m_upToDistance + connected->computeDistanceTo(Node::m_destinationNode);
            connected->m_rootNode = this;
            connected->m_internalState = Node::VISITED;
            processingList.push_back(connected);
        } else if (connected->m_internalState == Node::VISITED) {
            float accDistance = m_upToDistance + distance;
            float testValue = accDistance + connected->computeDistanceTo(Node::m_destinationNode);
            if (testValue < connected->m_value) {
                //Bessere Loesung gefunden
                connected->m_upToDistance = accDistance;
                connected->m_value = testValue;
                connected->m_rootNode = this;
            }
        }
    }
}

void Node::processBackwards() {
    Node* current = this;

    while (current) {
        current->m_internalState = Node::SOLUTION;
        current = current->m_rootNode;
    }

}

bool Node::isSolution() {
    if (m_internalState == SOLUTION) {
        return true;
    } else {
        return false;
    }
}

float Node::getWeight() {
    return m_value;
}

float Node::computeDistanceTo(Node* partnerNode) {
    float delta[2];

    delta[0] = partnerNode->m_coordinates[0] - m_coordinates[0];
    delta[1] = partnerNode->m_coordinates[1] - m_coordinates[1];

    return sqrtf(delta[0] * delta[0] + delta[1] * delta[1]);
}

string Node::toString() {
    ostringstream os;

    os << "X: " << m_coordinates[0] << " Y: " << m_coordinates[1];

    return os.str();
}
