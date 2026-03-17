#pragma once

class DynamicArray{
    public:
    DynamicArray(int size);
    ~DynamicArray();
    
    void push_back(int value);
    void set(int i, int value);
    int get(int i);
    int* find(int value);

    private:
        void resize();
        int* data;
        int size;
        int capacity;
};

DynamicArray::DynamicArray(int s):capacity(s), size(0){
    data = new int[s];
}

DynamicArray::~DynamicArray(){
    delete[] data;
}

void DynamicArray::push_back(int value){
    if(size == capacity){
        resize();
    }

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

void DynamicArray::set(int i, int value){
    data[i] = value;
}

int DynamicArray::get(int i){
    return data[i];
}

int* DynamicArray::find(int value){
    for(int i = 0; i < size; i++){
        if(data[i] == value) return &data[i];
    }
    return nullptr;
}