#pragma once

struct Node
{
    int data;
    Node* previous;
    Node* next;
    Node(int value) : data(value), next(nullptr){};
};

class DoublyLinkedList{
    public:
        DoublyLinkedList();
        ~DoublyLinkedList();

        void push_back(int value);
        void push_front(int value);
        void pop_back();
        void pop_front();
        void insert(int index, int value);
        int* find(int value);
    
    private:
        Node* head;
        Node* tail;
        int size;
};

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0){}

DoublyLinkedList::~DoublyLinkedList(){
    Node* current = head;

    while(current != nullptr){
        head = current->next;
        delete current;
        current = head;
    }
}

void DoublyLinkedList::push_back(int value){
    Node* newNode = new Node(value);
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }else{
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void DoublyLinkedList::push_front(int value){
    Node* newNode = new Node(value);
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }else{
        newNode->next = head;
        head = newNode;
    }
    size++;
}

void DoublyLinkedList::pop_back(){
    if(head == nullptr) return;

    if(head == tail){
        delete head;
        head == nullptr;
        tail == nullptr;
    }else{
        Node* tempNode = tail;
        tail = tail->previous;
        delete tempNode;
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
        Node* tempNode = head;
        head = head->next;
        delete tempNode;
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


    Node* current = head;
    for(int i = 0; i < index-1; i++){
        current = current->next;
    }
    
    Node* newNode = new Node(value);
    newNode->next = current->next;
    current->next = newNode;

    size++;
}

int* DoublyLinkedList::find(int value){
    Node* current = head;
    while(current != nullptr){
        if(current->data == value) return &(current->data); 
        current = current->next;
    }
    return nullptr;
}