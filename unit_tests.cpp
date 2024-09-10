#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>


using namespace std;


//Test singularity/plurality print outs
struct Node {
    string weStreet;
    string nsStreet;
    int treeAmount;
};

void displayStreetInfo(Node* nodePtr) {
    cout << "You have selected " << nodePtr->weStreet << " and " << nodePtr->nsStreet << ".\n";
    if (nodePtr->treeAmount == 1) {
        cout << "There is " << nodePtr->treeAmount << " tree on this street.\n";
    } else {
        cout << "There are " << nodePtr->treeAmount << " trees on this street.\n";
    }
}

//Initialize vector of test data
void testDisplayStreetInfo() {
    vector<Node> validStreets = {
        {"E Ermina", "1st Ave", 1},
        {"N Ruby", "2nd Ave", 5},
        {"E Augusta", "3rd Ave", 0}
    };

    //Test 1: Singular
    cout << "Expected: You have selected E Ermina and 1st Ave.\nThere is 1 tree on this street.\n";
    cout << "Actual: ";
    displayStreetInfo(&validStreets[0]);
    cout << "\n";

    //Test 2: Plural
    cout << "Expected: You have selected N Ruby and 2nd Ave.\nThere are 5 trees on this street.\n";
    cout << "Actual: ";
    displayStreetInfo(&validStreets[1]);
    cout << "\n";

    // Test 3: None
    cout << "Expected: You have selected E Augusta and 3rd Ave.\nThere are 0 trees on this street.\n";
    cout << "Actual: ";
    displayStreetInfo(&validStreets[2]);
    cout << "\n";
}

//Test forward/backward traversal

int main() {
    
    testDisplayStreetInfo();
    cout << "All tests completed!\n";

    return 0;
}
