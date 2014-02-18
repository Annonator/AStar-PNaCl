/* 
 * File:   NodeWrapper.h
 * Author: annonator
 *
 */

#ifndef NODEWRAPPER_H
#define	NODEWRAPPER_H

#include "Node.h"
#include <string>

using namespace std;

class NodeWrapper : public Node{
public:
    NodeWrapper();
    NodeWrapper(int id, float x, float y);
    NodeWrapper(const NodeWrapper& orig);
    virtual ~NodeWrapper();
    
    int getId();
    void setId(int set);
    string toString();
private:
    int m_id;
};

#endif	/* NODEWRAPPER_H */

