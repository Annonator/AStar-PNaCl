/* 
 * File:   AStarWrapper.cpp
 * Author: annonator
 * 
 * Created on 16. Februar 2014, 23:56
 */

#include "AStarWrapper.h"
#include "NodeWrapper.h"
#include <sstream>
#include <vector>

AStarWrapper::AStarWrapper() {
}

AStarWrapper::AStarWrapper(const AStarWrapper& orig) {
}

AStarWrapper::~AStarWrapper() {
}

string AStarWrapper::toString(){
    string res = "{\"array\":["; //"]}";
    
    Node* current = m_endNode;
    NodeWrapper* tmp = NULL;
    ostringstream os;
    
    vector<int> erg;
    
    while(current){
        tmp = (NodeWrapper*)current;
        erg.push_back(tmp->getId());
        current = current->getRoot();
    }
    int size = erg.size();
    
    os << erg[size-1];
            
    for(int i = size-2; i >= 0; --i){
        os << ", " << erg[i];
    }
    
    res += os.str();
    res += "]}";
    
    return res;
}
