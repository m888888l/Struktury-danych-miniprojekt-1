#pragma once
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "DoublyLinkedList.h"
#include "DynamicArray.h"
#include "SinglyLinkedList.h"

using namespace std;
using namespace std::chrono;

const int SIZES[8] = {1000000, 2000000, 3000000, 4000000,
                      5000000, 6000000, 7000000, 8000000};
const int SAMPLES = 100;
const int SEED = 420;

// Struktura przechowująca średnie czasy wykonania dla pojedyńczej operacji w 3
// strukturach
struct Results {
  unsigned long long arrTime;
  unsigned long long sllTime;
  unsigned long long dllTime;
};

class Tester {
public:
  Tester();
  ~Tester();
  void run(const string &outputFilename = "wyniki_testow.csv");

private:
  DynamicArray **d_arrays;
  SinglyLinkedList **s_lists;
  DoublyLinkedList **d_lists;
  void setupStructureDynamicArray(int currentSize);
  void setupStructureSinglyList(int currentSize);
  void setupStructureDoublyList(int currentSize);
  void cleanupStructureDynamicArray();
  void cleanupStructureSinglyList();
  void cleanupStructureDoublyList();
  void writeResultToFile(ofstream &file, int size, const string &opName,
                         const Results &res);
};

Tester::Tester() {};

Tester::~Tester() {};

// Przygotowywuje struktury z takimi samymi danymi
void Tester::setupStructureDynamicArray(int currentSize) {
  srand(SEED);
  d_arrays = new DynamicArray *[SAMPLES];
  for (int j = 0; j < SAMPLES; j++) {
    d_arrays[j] = new DynamicArray(5);
    for (int k = 0; k < currentSize; k++) {
      d_arrays[j]->push_back(rand());
    }
  }
}

void Tester::setupStructureSinglyList(int currentSize) {
  srand(SEED);
  s_lists = new SinglyLinkedList *[SAMPLES];
  for (int j = 0; j < SAMPLES; j++) {
    s_lists[j] = new SinglyLinkedList;
    for (int k = 0; k < currentSize; k++) {
      s_lists[j]->push_back(rand());
    }
  }
}

void Tester::setupStructureDoublyList(int currentSize) {
  srand(SEED);
  d_lists = new DoublyLinkedList *[SAMPLES];
  for (int j = 0; j < SAMPLES; j++) {
    d_lists[j] = new DoublyLinkedList;
    for (int k = 0; k < currentSize; k++) {
      d_lists[j]->push_back(rand());
    }
  }
}

// Zwalnia pamięć po strukturach
void Tester::cleanupStructureDynamicArray() {
  for (int i = 0; i < SAMPLES; i++) {
    delete d_arrays[i];
  }
  delete[] d_arrays;
}

void Tester::cleanupStructureSinglyList() {
  for (int i = 0; i < SAMPLES; i++) {
    delete s_lists[i];
  }
  delete[] s_lists;
}

void Tester::cleanupStructureDoublyList() {
  for (int i = 0; i < SAMPLES; i++) {
    delete d_lists[i];
  }
  delete[] d_lists;
}

// Metoda ułatwiająca zapis do pliku
void Tester::writeResultToFile(ofstream &file, int size, const string &opName,
                               const Results &res) {
  file << size << ";" << opName << ";" << res.arrTime << ";" << res.sllTime
       << ";" << res.dllTime << "\n";
}

// Główna metoda testująca
void Tester::run(const string &outputFilename) {
  ofstream file(outputFilename);
  file << "Rozmiar;Operacja;TablicaDynamiczna[ns];ListaJednokierunkowa[ns];"
          "ListaDwukierunkowa[ns]\n";

  for (int i = 0; i < sizeof(SIZES)/sizeof(int); i++) {
    // Wywołanie seeda po każdym zwiększeniu rozmiaru struktury ujednolica wynik
    srand(SEED);
    int currentSize = SIZES[i];

    // Losowanie wartości używanych w tej konkretnej iteracji
    int valToAdd = rand();
    int valToFind = rand() % currentSize;
    int randIndex = rand() % currentSize;

    // Zmienne przechowujące wyniki dla poszczególnych operacji
    Results pushBackRes, popBackRes, pushFrontRes, popFrontRes, insertRes,
        popRandRes, findRes;
    auto start = high_resolution_clock::now();
    auto end = start;

    cout<<"Size = "<<currentSize<<"\n";
    // // Mierzenie czasów związanych z tablicą dynamiczną
    setupStructureDynamicArray(currentSize);

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      d_arrays[i]->push_back(valToAdd);
    end = high_resolution_clock::now();
    pushBackRes.arrTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      d_arrays[i]->pop_at(currentSize);
    end = high_resolution_clock::now();
    popBackRes.arrTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      d_arrays[i]->insert(0, valToAdd);
    end = high_resolution_clock::now();
    pushFrontRes.arrTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      d_arrays[i]->pop_at(0);
    end = high_resolution_clock::now();
    popFrontRes.arrTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      d_arrays[i]->insert(randIndex, valToAdd);
    end = high_resolution_clock::now();
    insertRes.arrTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      d_arrays[i]->pop_at(randIndex);
    end = high_resolution_clock::now();
    popRandRes.arrTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++) {
      volatile int *res = d_arrays[i]->find(valToFind);
    }
    end = high_resolution_clock::now();
    findRes.arrTime = duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    cleanupStructureDynamicArray();

    // Mierzenie czasów związanych z listą jednokierunkową
    setupStructureSinglyList(currentSize);

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      s_lists[i]->push_back(valToAdd);
    end = high_resolution_clock::now();
    pushBackRes.sllTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      s_lists[i]->pop_at(randIndex);
    end = high_resolution_clock::now();
    popRandRes.sllTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      s_lists[i]->insert(randIndex, valToAdd);
    end = high_resolution_clock::now();
    insertRes.sllTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      s_lists[i]->pop_front();
    end = high_resolution_clock::now();
    popFrontRes.sllTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      s_lists[i]->push_front(valToAdd);
    end = high_resolution_clock::now();
    pushFrontRes.sllTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      s_lists[i]->pop_back();
    end = high_resolution_clock::now();
    popBackRes.sllTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++) {
      volatile int *res = s_lists[i]->find(valToFind);
    }
    end = high_resolution_clock::now();
    findRes.sllTime = duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    cleanupStructureSinglyList();

    // Mierzenie czasów związanych z listą dwukierunkową
    setupStructureDoublyList(currentSize);
    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      d_lists[i]->push_back(valToAdd);
    end = high_resolution_clock::now();
    pushBackRes.dllTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      d_lists[i]->pop_back();
    end = high_resolution_clock::now();
    popBackRes.dllTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      d_lists[i]->push_front(valToAdd);
    end = high_resolution_clock::now();
    pushFrontRes.dllTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      d_lists[i]->pop_front();
    end = high_resolution_clock::now();
    popFrontRes.dllTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      d_lists[i]->insert(randIndex, valToAdd);
    end = high_resolution_clock::now();
    insertRes.dllTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++)
      d_lists[i]->pop_at(randIndex);
    end = high_resolution_clock::now();
    popRandRes.dllTime =
        duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    start = high_resolution_clock::now();
    for (int i = 0; i < SAMPLES; i++) {
      volatile int *res = d_lists[i]->find(valToFind);
    }
    end = high_resolution_clock::now();
    findRes.dllTime = duration_cast<nanoseconds>(end - start).count() / SAMPLES;

    cleanupStructureDoublyList();

    // Zapisywanie wyników do pliku
    writeResultToFile(file, currentSize, "PushBack", pushBackRes);
    writeResultToFile(file, currentSize, "PopBack", popBackRes);
    writeResultToFile(file, currentSize, "PushFront", pushFrontRes);
    writeResultToFile(file, currentSize, "PopFront", popFrontRes);
    writeResultToFile(file, currentSize, "InsertRand", insertRes);
    writeResultToFile(file, currentSize, "PopRand", popRandRes);
    writeResultToFile(file, currentSize, "Find", findRes);
  }

  file.close();
}
