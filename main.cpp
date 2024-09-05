#include "linked_list.hpp"
#include "linked_list.cpp"

int main(){
    StreetList StreetObj;
    StreetObj.setup();

    StreetObj.printList();
    //Traversal
    cout << "Starting traversal:" << endl;
    StreetObj.interactiveTraversal();
    
    return 0;
}