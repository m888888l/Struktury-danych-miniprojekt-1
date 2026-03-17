#include <iostream>
#include <cstdlib>
#include "DynamicArray.h"
#include "SinglyLinkedList.h"

using namespace std;

int main(){
    DynamicArray* list = new DynamicArray(3);

    list->push_back(2);

    cout<<list->get(0);

    delete list;
return 0;
}