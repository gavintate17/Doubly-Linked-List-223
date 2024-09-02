#include "linked_list.hpp"

void StreetList::processStreets(ifstream* file){
    string junk;
    string street;
    bool end = false;

    getline(*file, junk);
    while (getline(*file, street) and !end){

        if (!street.empty()){
            weStreets.push_back(street);
        }
        else{
            end = true;
        }
    }
    end = false;

    while (getline(*file, street) and !end){

        if (!street.empty()){
            nsStreets.push_back(street);
        }
        else{
            end = true;
        }
    }
}

void StreetList::createAllNodes(){
    for (int i = 0; i < nsStreets.size() * weStreets.size(); i++){
        //Create a new node
        streetNode* newNode = new streetNode;
        newNode->nextNode = nullptr;

        //Linked list logic:
        if (headPtr == nullptr){ //Special case if the list is empty
            headPtr = newNode;
            newNode->previousNode = nullptr; //Set beginning of the list to nullptr
        }
        else{
            streetNode* nodePtr = headPtr;

            //Loops until nodePtr is the last in the list.
            while (nodePtr->nextNode != nullptr){
                nodePtr = nodePtr->nextNode;
            }

            nodePtr->nextNode = newNode; //Add the new node onto the end
            newNode->previousNode = nodePtr; //Keep track of the prvious node
        }
    }
}

void StreetList::initializeAllNodes(ifstream* file){
    bool end = false;

    streetNode* nodePtr = headPtr;
    for (int i = 0; i < weStreets.size() and nodePtr != nullptr; i++){
        for (int j = 0; j < nsStreets.size() and nodePtr != nullptr; j++){
            nodePtr->weStreet = weStreets[i];
            nodePtr->nsStreet = nsStreets[j];

            if (j == nsStreets.size() - 1){
                nodePtr->treeAmount = -2;
            }
            else{
                *file >> nodePtr->treeAmount;
            }

            nodePtr = nodePtr->nextNode;
        }
    }
}

void StreetList::setup(){
    ifstream inFile("tree_list.dat");
    processStreets(&inFile);
    createAllNodes();
    initializeAllNodes(&inFile);
    inFile.close();
}


//Prints the entire list
void StreetList::printList(){
    streetNode* nodePtr = headPtr;

    while (nodePtr != nullptr){
        cout << nodePtr->weStreet << " " << nodePtr->nsStreet << " " << nodePtr->treeAmount << "\n";

        nodePtr = nodePtr->nextNode;
    }
    cout << endl;
}