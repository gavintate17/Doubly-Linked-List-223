#include "linked_list.hpp"

int main(){
    StreetList StreetObj;
    StreetObj.setup();

    //StreetObj.printList(); -- Essentially handled this in the traversal
    //Traversal
    cout << "Starting traversal:" << endl;
    StreetObj.interactiveTraversal();
    
    return 0;
}