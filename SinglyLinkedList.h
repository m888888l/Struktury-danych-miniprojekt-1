#pragma once
#include <iostream>

struct Node //mala struktura przedstawiajaca jeden element
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
        void print();
        int* find(int value);
    
    private:
        Node* head; //wskaznik na pierwszy element
        Node* tail; //wskaznik na ostatni element
        int size; //niby niepotrzebne, mozna by zrobic na to metode, ale to jest bardziej wydajne, trzeba jednak pamietac aby zmieniac to pole w metodach zmieniajacych rozmiar
};

SinglyLinkedList::SinglyLinkedList() : head(nullptr), tail(nullptr), size(0){}

SinglyLinkedList::~SinglyLinkedList(){
    Node* current = head;

    while(current != nullptr){ //trzeba sobie zwolnic pamiec bo inaczej to sie nie zwolni :)
        head = current->next;
        delete current;
        current = head;
    }
}

void SinglyLinkedList::push_back(int value){
    Node* newNode = new Node(value); //alokuje pamiec dla nowego Node'a i przypisuje wskaznik na niego do newNode
    if(head == nullptr){ //jesli head == nullptr to znaczy ze lista jest pusta
        head = newNode;
        tail = newNode;
    }else{
        tail->next = newNode; //ostatni element teraz wksazuje na nowo dodany element zamiast na nullptr
        tail = newNode; //tail teraz wskazuje na nowy ostatni element
    }
    size++; //trzeba pamietac bo bedzie problem
}

void SinglyLinkedList::push_front(int value){
    Node* newNode = new Node(value); //to samo co wczesniej
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }else{
        newNode->next = head; //nowo dodany element wskazuje na pierwszy element list
        head = newNode;//head teraz wskazuje na nowy pierwszy element
    }
    size++;
}

void SinglyLinkedList::pop_back(){
    if(head == nullptr) return; //jesli lista jest pusta to nic nie robi

    if(head == tail){ //jesli head i tail wskazuja na to samo, to znaczy ze jest tylko jeden element
        delete head;
        head = nullptr;
        tail = nullptr;
    }else{
        Node* current = head;//lista jednokierunkowa, a wiec trzeba leciec od przodu
        while(current->next != tail){ //lecimy az current nie wskazuje na przedostatni element
            current = current->next;
        }
        delete tail;//zwlaniamy pamiec w ktorej byl ostatni element
        tail = current;//tail wskazuje na przedostatni element (teraz w sumie juz ostatni)
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
        Node* tempNode = head;//tymczasowy wskaznik, zeby bylo wiadomo jaka pamiec zwolnic
        head = head->next;//head wskazuje teraz na drugi element (zaraz pierwszy)
        delete tempNode;//zwalnia pamiec po pierwszym elemencie
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
    for(int i = 0; i < index-1; i++){//lecimy az bedziemy na elemencie przed elementem ktory chcemy usunac
        current = current->next;
    }

    Node* deleted = current->next; //wskaznik tymczasowy do przechowywania adresu z ktorego pamiec chcemy zwolnic
    current->next = deleted->next; //element przed tym ktory usuwamy teraz wskazuje na element za tym ktory usuwamy
    delete deleted; //zwlaniamy pamiec po usuwamyn elemencie

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


    Node* current = head; //robimy sobie "iterator"
    for(int i = 0; i < index-1; i++){//lecimy az current bedzie wskazywac na element za ktorym chcemy wstawic nowy element
        current = current->next;
    }
    
    Node* newNode = new Node(value); //alokujemy pamiec dla nowego elementu i od razu przypisujemy mu wartosc
    newNode->next = current->next;//nowy element wskazuje na to na co wskazuje element przed nim
    current->next = newNode;//element przed nim poprawnie teraz wskazuje na nowy element

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

void SinglyLinkedList::print() {
  Node *current = head;
  std::cout << "Head -> ";
  while (current != nullptr) {
    std::cout << current->data << " -> ";
    current = current->next;
  }
  std::cout << "NULL\n";
}
