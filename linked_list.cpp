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

void StreetList::interactiveTraversal() {
    streetNode* nodePtr = headPtr;
    vector<streetNode*> validStreets;  // To store pointers to valid intersections

    if (nodePtr == nullptr) {
        cout << "The list is empty.\n";
        return;
    }

    // Gather valid street nodes into the validStreets vector, excluding ones with -2 or -1 trees
    while (nodePtr != nullptr) {
        if (nodePtr->treeAmount != -2 && nodePtr->treeAmount != -1) {  // Exclude intersections with -2 or -1 trees
            validStreets.push_back(nodePtr);  // Store the pointer to the node
        }
        nodePtr = nodePtr->nextNode;
    }

    int choice;
    char continueChoice;
    char directionChoice;

    // Loop to keep asking for input
    do {
        // Print all available streets
        cout << "\nAvailable streets:\n";
        for (size_t i = 0; i < validStreets.size(); ++i) {
            cout << i + 1 << ". " << validStreets[i]->weStreet << " and " << validStreets[i]->nsStreet << "\n";
        }

        // Ask to choose a street
        cout << "Enter the number of the street you want to check (or 0 to quit): ";
        cin >> choice;

        // Validate input
        if (choice == 0) {
            cout << "Exiting traversal.\n";
            return;
        } else if (choice < 1 || choice > validStreets.size()) {
            cout << "Invalid selection. Please try again.\n";
            continue;
        }

        // Display the selected street and tree amount
        nodePtr = validStreets[choice - 1];  // Get the selected street node
        cout << "You have selected " << nodePtr->weStreet << " and " << nodePtr->nsStreet << ".\n";
        if (nodePtr->treeAmount == 1) {
            cout << "There is " << nodePtr->treeAmount << " tree at " << nodePtr->weStreet << " and " << nodePtr->nsStreet << ".\n";
        }
        else {
            cout << "There are " << nodePtr->treeAmount << " trees at " << nodePtr->weStreet << " and " << nodePtr->nsStreet << ".\n";
        }

        // Keep asking if the user wants to go forward or backward until they want to stop
        do {
            // Ask if they want to move forward or backward
            cout << "Do you want to move forward (f) or backward (b) in the list? (f/b, or 'n' to stop): ";
            cin >> directionChoice;

            if (directionChoice == 'n' || directionChoice == 'N') {
                cout << "Stopping traversal for the current selection.\n";
                break;  // Exit the inner loop and ask if they want to select a new intersection
            }

            // Handle forward or backward movement in the list
            if (directionChoice == 'f' || directionChoice == 'F') {
                if (nodePtr->nextNode != nullptr) {
                    nodePtr = nodePtr->nextNode;
                    cout << "Moving forward to: " << nodePtr->weStreet << " and " << nodePtr->nsStreet << ".\n";
                } else {
                    cout << "No further streets in the list.\n";
                }
            } else if (directionChoice == 'b' || directionChoice == 'B') {
                // Traverse backwards by searching through the validStreets list
                for (size_t i = 0; i < validStreets.size(); ++i) {
                    if (validStreets[i] == nodePtr && i > 0) {
                        nodePtr = validStreets[i - 1];
                        cout << "Moving backward to: " << nodePtr->weStreet << " and " << nodePtr->nsStreet << ".\n";
                        break;
                    } else if (i == 0) {
                        cout << "No previous streets in the list.\n";
                        break;
                    }
                }
            } else {
                cout << "Invalid direction choice. Please try again.\n";
            }

        } while (true);  // Loop until the user chooses to stop forward/backward traversal

        // Ask if the user wants to pick another intersection
        cout << "Do you want to pick another intersection? (y/n): ";
        cin >> continueChoice;

        if (continueChoice == 'n' || continueChoice == 'N') {
            cout << "Exiting traversal.\n";
            return;
        }

    } while (true);  // Loop until you decide to quit
}

StreetList::~StreetList() { //Deconstructor
    streetNode* nodePtr = headPtr;
    while (nodePtr != nullptr) {
        streetNode* nextNode = nodePtr->nextNode;
        delete nodePtr;
        nodePtr = nextNode;
    }
}