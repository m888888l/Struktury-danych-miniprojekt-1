#pragma once
#include <iostream>

class DynamicArray{
    public:
    DynamicArray(int size);
    ~DynamicArray();
    
    void push_back(int value);
    void set(int index, int value);
    void pop_at(int index);
    void pop_back();
    void insert(int index, int value);
    void print();
    int* get(int index);
    int* find(int value);

    private:
        void resize(); //metoda pomocnicza do powiekszenia tablicy
        int* data;
        int size; //ilosc elementow
        int capacity; //rozmiar tablicy
};

DynamicArray::DynamicArray(int s) : capacity(s), size(0){
    data = new int[s]; //alokuje pamiec o rozmiarze s*sizeof(int) i przypisuje wskaznik tej pamieci do data
}

DynamicArray::~DynamicArray(){
    delete[] data; //trzeba zwolnic pamiec tablicy :)
}

void DynamicArray::push_back(int value){
    if(size == capacity) resize(); //dodanie elementu, a co za tym idzie sprawdzenie czy nie wyjdzie poza rozmiar tablicy

    data[size] = value;
    size++;
}

void DynamicArray::resize(){
    capacity = 2 * capacity;

    int* tempData = new int[capacity]; //wskaznik na nowo zaalokowana pamiec dla tablicy o podwojonym rozmiarze

    for(int i = 0; i < size; i++){ //kopiowanie wartosci ze starej tablicy do nowej
        tempData[i] = data[i];
    }

    delete[] data; //zwolnienie pamieci w ktorej miescila sie stara tablica

    data = tempData;
}

void DynamicArray::set(int index, int value){
    if(index < 0 || index >= size) return; //sprawdza czy indeks miesci sie w rozmiarze tablicy
    data[index] = value;
}

int* DynamicArray::get(int index){
    if(index < 0 || index >= size) return nullptr; //sprawdza czy indeks miesci sie w rozmiarze tablicy
    return &(data[index]);
}

int* DynamicArray::find(int value){
    for(int i = 0; i < size; i++){
        if(data[i] == value) return &data[i];
    }
    return nullptr; //jak nie znajdzie elementu, zwraca nullptr
}

void DynamicArray::pop_at(int index){
    if(index < 0 || index >= size) return; 
    for(int i = index; i < size-1; i++){//kazdy element od data[index] staje sie kolejnym elementem, efektywnie usuwa element data[index] 
        data[i] = data[i+1];
    }
    size--;
}

void DynamicArray::pop_back(){
    size--; //
}

void DynamicArray::insert(int index, int value){
    if(index < 0 || index > size) return;
    if(size == capacity) resize(); //dodanie elementu, wiec trzeba sprawdzic czy sie zmiesci i powiekszyc tablice jak nie

    for(int i = size; i > index; i--){//przesuwa wszystkie elementu od konca do data[index] wlacznie o 1 w prawo
        data[i] = data[i-1];
    }

    data[index] = value;
    size++;
}

void DynamicArray::print() {
  std::cout << "[ ";
  for (int i = 0; i < size; i++) {
    std::cout << data[i] << " ";
  }
  std::cout << "]\n";
}