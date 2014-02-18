/* 
 * File:   AStarWrapper.h
 * Author: annonator
 *
 * Created on 16. Februar 2014, 23:56
 */

#ifndef ASTARWRAPPER_H
#define	ASTARWRAPPER_H

#include "AStar.h"
#include <string>

class AStarWrapper : public AStar{
public:
    AStarWrapper();
    AStarWrapper(const AStarWrapper& orig);
    virtual ~AStarWrapper();
    
    //liefere Zielreihenfolge als JSON array
    string toString();
private:

};

#endif	/* ASTARWRAPPER_H */

