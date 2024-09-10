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


void StreetList::initializeAllDistances(ifstream* file){

    streetNode* nodePtr = headPtr;
    string word;
    int number;
    int counter = 0;
    vector <int> distances;
    
    while (!(*file).eof()) {
        if (*file >> number) {
            distances.push_back(number);
        } else {
            //if extraction fails, clear the error state and ignore the bad input
            file->clear();
            file->ignore();
        }
        }
        
    for (int i = 0; i < weStreets.size() and nodePtr != nullptr and counter < distances.size(); i++){
        for (int j = 0; j < nsStreets.size() and nodePtr != nullptr and counter < distances.size(); j++){

            if (j == nsStreets.size() - 1){
                nodePtr->treeDistance = -2;
            }
            else{
                nodePtr->treeDistance = distances.at(counter++);

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
    initializeAllDistances(&inFile);
    inFile.close();
}

//Prints the entire list
void StreetList::printList(){
    streetNode* nodePtr = headPtr;
    int counter = 0;
    while (nodePtr->nextNode != nullptr){

        if (nodePtr->treeAmount >= 0){

            cout << counter + 1 << ". Between " << nodePtr->nsStreet << " and ";
            cout << nodePtr->nextNode->nsStreet << " on " << nodePtr->weStreet << ".\n";
        }
        counter++;
        nodePtr = nodePtr->nextNode;
    }
    cout << endl;
    validStreetCount = counter;
}

void StreetList::interactiveTraversal() {
    streetNode* nodePtr = nullptr;  // Pointer to hold the currently selected node

    if (headPtr == nullptr) {
        cout << "The list is empty.\n";
        return;
    }

    int choice;
    char continueChoice;
    char directionChoice;

    // Loop to keep asking for input
    do {
        // Print all available streets
        cout << "\nAvailable streets:\n";
        printList();

        // Ask the user to input street names to search for
        int num = 0;
        bool loop = true;
        while (loop == true){
            cout << "Enter street number:\n";
            cin >> num;
            if (num < 1 or num > validStreetCount) {
                cout << "Invalid number" << endl;
            }
            else{
                loop = false;
            }
        }
        nodePtr = search(num);

        // Display the selected street and tree amount
        cout << "You have selected " << nodePtr->weStreet << ", between " << nodePtr->nsStreet << " and " << nodePtr->nextNode->nsStreet << ".\n";
        printTrees(nodePtr);

        // Keep asking if the user wants to go forward or backward until they want to stop
        do {
            // Ask if they want to move forward or backward
            cout << "\nDo you want to move forward (f) or backward (b) in the list? (f/b, or 'n' to stop): ";
            cin >> directionChoice;

            if (directionChoice == 'n' || directionChoice == 'N') {
                cout << "Stopping traversal for the current selection.\n";
                break;  // Exit the inner loop and ask if they want to select a new intersection
            }

            // Handle forward or backward movement in the list
            if (directionChoice == 'f' || directionChoice == 'F') {
                if (nodePtr->nextNode == nullptr || nodePtr->nextNode->treeAmount == -2) {
                    cout << "No further streets on " << nodePtr->weStreet << ".\n";
                }
                else if (nodePtr->nextNode->treeAmount == -1) {  // Skip over the school
                    nodePtr = nodePtr->nextNode;
                    cout << "Skipping school zone.\n";
                }
                else {
                    nodePtr = nodePtr->nextNode;
                    cout << "Moving forward to: " << nodePtr->weStreet << ", between ";
                    cout << nodePtr->nsStreet << " and " << nodePtr->nextNode->nsStreet << ".\n";
                    printTrees(nodePtr);
                }
            } 
            else if (directionChoice == 'b' || directionChoice == 'B') {
                if (nodePtr->previousNode == nullptr || nodePtr->previousNode->treeAmount == -2) {
                    cout << "No previous streets on " << nodePtr->weStreet << ".\n";
                }
                else if (nodePtr->previousNode->treeAmount == -1) {  // Skip over the school
                    nodePtr = nodePtr->previousNode;
                    cout << "Skipping school zone.\n";
                }
                else {
                    nodePtr = nodePtr->previousNode;
                    cout << "Moving backward to: " << nodePtr->weStreet << ", between ";
                    cout << nodePtr->nsStreet << " and " << nodePtr->nextNode->nsStreet << ".\n";
                    printTrees(nodePtr);
                }
            } 
            else {
                cout << "Invalid direction choice. Please try again.\n";
            }

        } while (true);  // Loop until the user chooses to stop forward/backward traversal

        // Ask if the user wants to pick another intersection
        cout << "Do you want to pick another street section? (y/n): ";
        cin >> continueChoice;
        cin.ignore();
        if (continueChoice == 'n' || continueChoice == 'N') {
            cout << "Exiting traversal.\n";
            return;
        }

    } while (true);  // Loop until you decide to quit
}

void StreetList::printTrees(streetNode* nodePtr){
    if (nodePtr->treeAmount == 1) {
                cout << "There is " << nodePtr->treeAmount << " tree at " << nodePtr->weStreet;
                cout << ", between " << nodePtr->nsStreet << " and " << nodePtr->nextNode->nsStreet << ".\n";
            }
            else {
                cout << "There are " << nodePtr->treeAmount << " trees at " << nodePtr->weStreet;
                cout << ", between " << nodePtr->nsStreet << " and " << nodePtr->nextNode->nsStreet << ".\n";
                cout << "Each tree is about " << nodePtr->treeDistance << "ft apart.\n";
            }
}

StreetList::~StreetList() { //Deconstructor
    streetNode* nodePtr = headPtr;
    while (nodePtr != nullptr) {
        streetNode* nextNode = nodePtr->nextNode;
        delete nodePtr;
        nodePtr = nextNode;
    }
}

StreetList::streetNode* StreetList::search(int num){
    streetNode* nodePtr = headPtr;
    int counter = 0;
    while (++counter < num) {

        nodePtr = nodePtr->nextNode;  // Move to the next node
    }
    return nodePtr;
}