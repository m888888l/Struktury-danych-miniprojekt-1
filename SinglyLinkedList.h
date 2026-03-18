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
        void pop_at(int index);
        void insert(int index, int value);
        int* find(int value);
    
    private:
        Node* head;
        Node* tail;
        int size;
};

SinglyLinkedList::SinglyLinkedList() : head(nullptr), tail(nullptr), size(0){}

SinglyLinkedList::~SinglyLinkedList(){
    Node* current = head;

    while(current != nullptr){
        head = current->next;
        delete current;
        current = head;
    }
}

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
        head = nullptr;
        tail = nullptr;
    }else{
        Node* current = head;
        while(current->next != tail){
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

    if(head == tail){
        delete head;
        head = nullptr;
        tail = nullptr;
    }else{
        Node* tempNode = head;
        head = head->next;
        delete tempNode;
    }
    size--;
}

void SinglyLinkedList::pop_at(int index){
    if(index < 0 || index >= size) return;
    if(index == 0){
        pop_front();
        return;
    };
    if(index == size-1){
        pop_back();
        return;
    }

    Node* current = head;
    for(int i = 0; i < index-1; i++){
        current = current->next;
    }

    Node* deleted = current->next;
    current->next = deleted->next;
    delete deleted;

    size--;
}

void SinglyLinkedList::insert(int index, int value){
    if(index < 0 || index > size) return; //jak index wychodzi poza liste to funkcja sie konczy
    if(head == nullptr || index == 0){ //jesli lista jest pusta lub insertujemy na poczatek uzywamy metody push_front
        push_front(value);
        return;
    }
    if(index == size){ //jesli insertujemy na koniec uzywamy push_back
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

int* SinglyLinkedList::find(int value){
    Node* current = head;
    while(current != nullptr){
        if(current->data == value) return &(current->data); 
        current = current->next;
    }
    return nullptr;
}