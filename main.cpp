#include <iostream>
#include <cstdlib>
#include "DynamicArray.h"
#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

using namespace std;

int main(){
    srand(0);
    DynamicArray* d_array = new DynamicArray(5);
    SinglyLinkedList* s_list = new SinglyLinkedList;
    DoublyLinkedList* d_list = new DoublyLinkedList;


    int now = 0;

    for(int i = 0; i < 5; i++){
        now = rand();
        d_array->push_back(now);
        s_list->push_back(now);
        d_list->push_back(now);
    }


    cout<<*(d_array->find(2437))<<"\n";
    cout<<*(s_list->find(2437))<<"\n";
    cout<<*(d_list->find(2437))<<"\n";



return 0;
}