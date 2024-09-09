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

    int validStreetCount;
    //Class functions
    void setup();
    void printList(bool nums);

    //Traversal functions
    void interactiveTraversal();

    //Necessary functions:
    //Insert, Still needed
    // Delete, Destructor already does this???
    // Printing, still needs to print in geographic representation as well
    // Search, Still needed. Takes int referring to a node and returns a pointer to that node
    //
    //
};



//Other function defs:

#endif