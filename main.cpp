#include "linked_list.hpp"
#include "linked_list.cpp"

using namespace std;

int main(){

    StreetList StreetObj;
    StreetObj.setup();

    //StreetObj.printList(); -- Essentially handled this in the traversal
    //Traversal
    cout << "Starting traversal:" << endl;
    StreetObj.interactiveTraversal();
    
    return 0;
}