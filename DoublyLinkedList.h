#pragma once
#include <iostream>

struct DoubleNode//struktura przechowujaca 1 element, teraz z polem previous wskazujacym na poprzedni element
{
    int data;
    DoubleNode* previous;
    DoubleNode* next;
    DoubleNode(int value) : data(value), next(nullptr), previous(nullptr){};
};

class DoublyLinkedList{
    public:
        DoublyLinkedList();
        ~DoublyLinkedList();

        void push_back(int value);
        void push_front(int value);
        void pop_back();
        void pop_front();
        void pop_at(int index);
        void insert(int index, int value);
        void print();
        int* find(int value);
    
    private:
        DoubleNode* head;
        DoubleNode* tail;
        int size;
};

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0){}

DoublyLinkedList::~DoublyLinkedList(){
    DoubleNode* current = head;

    while(current != nullptr){
        head = current->next;
        delete current;
        current = head;
    }
}

void DoublyLinkedList::push_back(int value){
    DoubleNode* newDoubleNode = new DoubleNode(value);
    if(head == nullptr){
        head = newDoubleNode;
        tail = newDoubleNode;
    }else{
        tail->next = newDoubleNode;
        newDoubleNode->previous = tail;
        tail = newDoubleNode;
    }
    size++;
}

void DoublyLinkedList::push_front(int value){
    DoubleNode* newDoubleNode = new DoubleNode(value);
    if(head == nullptr){
        head = newDoubleNode;
        tail = newDoubleNode;
    }else{
        newDoubleNode->next = head;
        head->previous = newDoubleNode;
        head = newDoubleNode;
    }
    size++;
}

void DoublyLinkedList::pop_back(){//to jest prostsze niz w liscie jednokierunkowej
    if(head == nullptr) return;

    if(head == tail){
        delete head;
        head = nullptr;
        tail = nullptr;
    }else{
        DoubleNode* tempDoubleNode = tail;
        tail = tail->previous;
        tail->next=nullptr;
        delete tempDoubleNode;
    }

    size--;
}

void DoublyLinkedList::pop_front(){
    if(head == nullptr) return;

    if(head == tail){
        delete head;
        head == nullptr;
        tail == nullptr;
    }else{
        DoubleNode* tempDoubleNode = head;
        head = head->next;
        head->previous = nullptr;
        delete tempDoubleNode;
    }

    size--;
}

void DoublyLinkedList::pop_at(int index){
    if(index < 0 || index >= size) return;
    if(index == 0){
        pop_front();
        return;
    }
    if(index == size-1){
        pop_back();
        return;
    }

    if(index < size/2){ //implementacja taka sama jak w singly linked list, z ta roznica ze liczmy czy szybciej leciec od konca czy od przodu
        DoubleNode* current = head;
        for(int i = 0; i < index-1; i++){
            current = current->next;
        }

        DoubleNode* deleted = current->next;
        current->next = deleted->next;
        (deleted->next)->previous = current;
        delete deleted;
    }else{
        DoubleNode* current = tail;
        for(int i = size-1; i > index+1; i--){
            current = current->previous;
        }

        DoubleNode* deleted = current->previous;
        current->previous = deleted->previous;
        (deleted->previous)->next = current;
        delete deleted;
    }

    size--;
}

void DoublyLinkedList::insert(int index, int value){
    if(index < 0 || index > size) return;
    if(head == nullptr || index == 0){
        push_front(value);
        return;
    }
    if(index == size){
        push_back(value);
        return;
    }

    if(index < size/2){//implementacja taka sama jak w singly linked list, z ta roznica ze liczmy czy szybciej leciec od konca czy od przodu

        DoubleNode* current = head;
        for(int i = 0; i < index-1; i++){
            current = current->next;
        }
        
        DoubleNode* newDoubleNode = new DoubleNode(value);
        
        newDoubleNode->next = current->next;
        current->next = newDoubleNode;
        newDoubleNode->previous = current;
        (newDoubleNode->next)->previous = newDoubleNode;
        
    }else{
        DoubleNode* current = tail;
        for(int i = size-1; i > index; i--){
            current = current->previous;
        }
        
        DoubleNode* newDoubleNode = new DoubleNode(value);
        
        newDoubleNode->previous = current->previous;
        current->previous = newDoubleNode;
        newDoubleNode->next = current;
        (newDoubleNode->previous)->next = newDoubleNode;
    }

    size++;
}

int* DoublyLinkedList::find(int value){
    DoubleNode* current = head;
    while(current != nullptr){
        if(current->data == value) return &(current->data); 
        current = current->next;
    }
    return nullptr;
}

void DoublyLinkedList::print() {
  DoubleNode *current = head;
  std::cout << "Head <-> ";
  while (current != nullptr) {
    std::cout << current->data << " <-> ";
    current = current->next;
  }
  std::cout << "NULL\n";
}