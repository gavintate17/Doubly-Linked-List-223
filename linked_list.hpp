#ifndef HEADER_H
#define HEADER_H

//Libraries to be included:
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Class
class StreetList{
    private:

    vector <string> weStreets;
    vector <string> nsStreets;

    struct streetNode{
        string nsStreet; //going north to south
        string weStreet; //going west to east
        int treeAmount;
        streetNode* previousNode;
        streetNode* nextNode;
    };

    streetNode* headPtr;

    void processStreets(ifstream* file);
    void createAllNodes();
    void initializeAllNodes(ifstream* file);

    public:
    //Default constructor
    StreetList(){headPtr = nullptr;}
    //Destructor
    //Not yet implemented, should clear the heap.
    ~StreetList(){}

    //Class functions
    void setup();
    void printList();

};



//Other function defs:

#endif