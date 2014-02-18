/* 
 * File:   Node.h
 * Author: annonator
 *
 */

#ifndef NODE_H
#define	NODE_H

#include <vector>
#include <string>
#include <math.h>

using namespace std;

class Node {
public:
    Node();
    Node(float x, float y);
    Node(const Node& orig);
    virtual ~Node();

    void init(float x, float y);
    
    Node* getRoot();

    static void setDestinationNode(Node* destination);
    //Stellt verbindung zu anderem Knoten her
    void connectWith(Node* otherNode);
    void resetConnections();
    //Setzt Status von Node zurück für neue Berechnung
    void reset(bool isStartNode);
    //Nimmt Node in processing list auf und bestimmt naechsten node
    void setActiveNode(vector<Node*>& processingList);
    //Baut den Besten Pfad rückwärts auf
    void processBackwards();
    //Prüft ob aktueller Node die Loesung ist
    bool isSolution();
    //Liefert die Kosten diese Knotens
    float getWeight();
    //Berechnet Abstand zu anderen Konten
    float computeDistanceTo(Node* partnerNode);

    string toString();

protected:

    float m_coordinates[2];

    struct Link {
        Node* linkedNode;

        float distance;
    };

    vector<Link> m_connectedNodes;

    enum State {
        INITIAL,
        VISITED,
        CLOSED,
        SOLUTION
    };

    State m_internalState;

    float m_upToDistance;
    float m_value;

    Node* m_rootNode;

    static Node* m_destinationNode;

};

#endif	/* NODE_H */

