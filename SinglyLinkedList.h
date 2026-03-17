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
        int find(int value);
    
    private:
        Node* head;
        Node* tail;
        int size;

};
