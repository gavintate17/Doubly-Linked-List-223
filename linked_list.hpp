#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

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
    ~StreetList();

    //Class functions
    void setup();
    void printList();

    //Traversal functions
    void interactiveTraversal();

    //Functions to add: (Insert, Delete, Printing, Search)

};



//Other function defs:

#endif