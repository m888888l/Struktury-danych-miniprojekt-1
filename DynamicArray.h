#pragma once

class DynamicArray{
    public:
    DynamicArray(int size);
    ~DynamicArray();
    
    void push_back(int value);
    void set(int index, int value);
    void insert(int index, int value);
    int get(int index);
    int* find(int value);

    private:
        void resize();
        int* data;
        int size;
        int capacity;
};

DynamicArray::DynamicArray(int s) : capacity(s), size(0){
    data = new int[s];
}

DynamicArray::~DynamicArray(){
    delete[] data;
}

void DynamicArray::push_back(int value){
    if(size == capacity) resize();

    data[size] = value;
    size++;
}

void DynamicArray::resize(){
    capacity = 2 * capacity;

    int* tempData = new int[capacity];

    for(int i = 0; i < size; i++){
        tempData[i] = data[i];
    }

    delete[] data;

    data = tempData;
}

void DynamicArray::set(int index, int value){
    if(index < 0 || index >= size) return;
    data[index] = value;
}

int DynamicArray::get(int index){
    if(index < 0 || index >= size) return;
    return data[index];
}

int* DynamicArray::find(int value){
    for(int i = 0; i < size; i++){
        if(data[i] == value) return &data[i];
    }
    return nullptr;
}

void DynamicArray::insert(int index, int value){
    if(index < 0 || index > size) return;
    if(size == capacity) resize();

    for(int i = size; i > index; i--){
        data[i] = data[i-1];
    }

    data[index] = value;
    size++;
}