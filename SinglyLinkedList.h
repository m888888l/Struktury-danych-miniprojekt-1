#pragma once

struct Node
{
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr){};
};

class SinglyLinkedList{
    public:
        SinglyLinkedList();
        ~SinglyLinkedList();

        void push_back(int value);
        void push_front(int value);
        void pop_back();
        void pop_front();
        void insert(int index, int value);
        int find(int value);
    
    private:
        Node* head;
        Node* tail;
        int size;
};

SinglyLinkedList::SinglyLinkedList() : head(nullptr), tail(nullptr), size(0){}

void SinglyLinkedList::push_back(int value){
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

void SinglyLinkedList::push_front(int value){
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

void SinglyLinkedList::pop_back(){
    if(head == nullptr) return;

    if(head == tail){
        delete head;
        head == nullptr;
        tail == nullptr;
    }else{
        Node* current = head;
        while(current->next != head){
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
    }

    size--;
}

void SinglyLinkedList::pop_front(){
    if(head == nullptr) return;

    Node* tempNode = head;
    head = head->next;
    delete tempNode;

    size--;
}

void SinglyLinkedList::insert(int index, int value){
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