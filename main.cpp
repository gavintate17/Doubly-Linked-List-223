#include "linked_list.hpp"

int main(){
    StreetList StreetObj;
    StreetObj.setup();

    //Traversal
    cout << "Starting traversal:" << endl;
    StreetObj.interactiveTraversal();
    
    return 0;
}