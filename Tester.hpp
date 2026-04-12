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

const int sizes[8] = {7812,   15625,  31250,  62500,
                      125000, 250000, 500000, 1000000};
const int samples = 100;

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
  void setupStructures(int currentSize);
  void cleanupStructures();
  void writeResultToFile(ofstream &file, int size, const string &opName,
                         const Results &res);
};

Tester::Tester() {};

Tester::~Tester() {};

// Przygotowywuje struktury z takimi samymi danymi
void Tester::setupStructures(int currentSize) {
  int now = 0;

  d_arrays = new DynamicArray *[samples];
  s_lists = new SinglyLinkedList *[samples];
  d_lists = new DoublyLinkedList *[samples];
  for (int j = 0; j < samples; j++) {
    d_arrays[j] = new DynamicArray(5);
    s_lists[j] = new SinglyLinkedList;
    d_lists[j] = new DoublyLinkedList;
    for (int k = 0; k < currentSize; k++) {
      now = rand();
      d_arrays[j]->push_back(now);
      s_lists[j]->push_back(now);
      d_lists[j]->push_back(now);
    }
  }
}

// Zwalnia pamięć po strukturach
void Tester::cleanupStructures() {
  for (int i = 0; i < samples; i++) {
    delete d_arrays[i];
    delete s_lists[i];
    delete d_lists[i];
  }
  delete[] d_arrays;
  delete[] s_lists;
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

  for (int i = 0; i < sizeof(sizes)/sizeof(int); i++) {
    // Wywołanie seeda po każdym zwiększeniu rozmiaru struktury ujednolica wynik
    srand(420);
    int currentSize = sizes[i];

    // Losowanie wartości używanych w tej konkretnej iteracji
    int valToAdd = rand();
    int valToFind = rand() % currentSize;
    int randIndex = rand() % currentSize;

    setupStructures(currentSize);

    // Zmienne przechowujące wyniki dla poszczególnych operacji
    Results pushBackRes, popBackRes, pushFrontRes, popFrontRes, insertRes,
        popRandRes, findRes;
    auto start = high_resolution_clock::now();
    auto end = start;

    // Mierzenie czasu dodawania elementu na koniec
    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      d_arrays[i]->push_back(valToAdd);
    end = high_resolution_clock::now();
    pushBackRes.arrTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      s_lists[i]->push_back(valToAdd);
    end = high_resolution_clock::now();
    pushBackRes.sllTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      d_lists[i]->push_back(valToAdd);
    end = high_resolution_clock::now();
    pushBackRes.dllTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    // Mierzenie czasu usuwania elementu z końca
    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      d_arrays[i]->pop_at(currentSize);
    end = high_resolution_clock::now();
    popBackRes.arrTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      s_lists[i]->pop_back();
    end = high_resolution_clock::now();
    popBackRes.sllTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      d_lists[i]->pop_back();
    end = high_resolution_clock::now();
    popBackRes.dllTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    // Mierzenie czasu dodawania elementu na początek
    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      d_arrays[i]->insert(0, valToAdd);
    end = high_resolution_clock::now();
    pushFrontRes.arrTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      s_lists[i]->push_front(valToAdd);
    end = high_resolution_clock::now();
    pushFrontRes.sllTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      d_lists[i]->push_front(valToAdd);
    end = high_resolution_clock::now();
    pushFrontRes.dllTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    // Mierzenie czasu usuwania elementu z początku
    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      d_arrays[i]->pop_at(0);
    end = high_resolution_clock::now();
    popFrontRes.arrTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      s_lists[i]->pop_front();
    end = high_resolution_clock::now();
    popFrontRes.sllTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      d_lists[i]->pop_front();
    end = high_resolution_clock::now();
    popFrontRes.dllTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    // Mierzenie czasu dodawania elementu w losowe miejsce
    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      d_arrays[i]->insert(randIndex, valToAdd);
    end = high_resolution_clock::now();
    insertRes.arrTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      s_lists[i]->insert(randIndex, valToAdd);
    end = high_resolution_clock::now();
    insertRes.sllTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      d_lists[i]->insert(randIndex, valToAdd);
    end = high_resolution_clock::now();
    insertRes.dllTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    // Usuwanie losowego elementu
    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      d_arrays[i]->pop_at(randIndex);
    end = high_resolution_clock::now();
    popRandRes.arrTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      s_lists[i]->pop_at(randIndex);
    end = high_resolution_clock::now();
    popRandRes.sllTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++)
      d_lists[i]->pop_at(randIndex);
    end = high_resolution_clock::now();
    popRandRes.dllTime =
        duration_cast<nanoseconds>(end - start).count() / samples;

    // Znajdywanie losowego elementu
    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++) {
      volatile int *res = d_arrays[i]->find(valToFind);
    }
    end = high_resolution_clock::now();
    findRes.arrTime = duration_cast<nanoseconds>(end - start).count() / samples;

    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++) {
      volatile int *res = s_lists[i]->find(valToFind);
    }
    end = high_resolution_clock::now();
    findRes.sllTime = duration_cast<nanoseconds>(end - start).count() / samples;

    start = high_resolution_clock::now();
    for (int i = 0; i < samples; i++) {
      volatile int *res = d_lists[i]->find(valToFind);
    }
    end = high_resolution_clock::now();
    findRes.dllTime = duration_cast<nanoseconds>(end - start).count() / samples;

    // Zapisywanie wyników do pliku
    writeResultToFile(file, currentSize, "PushBack", pushBackRes);
    writeResultToFile(file, currentSize, "PopBack", popBackRes);
    writeResultToFile(file, currentSize, "PushFront", pushFrontRes);
    writeResultToFile(file, currentSize, "PopFront", popFrontRes);
    writeResultToFile(file, currentSize, "InsertRand", insertRes);
    writeResultToFile(file, currentSize, "PopRand", popRandRes);
    writeResultToFile(file, currentSize, "Find", findRes);

    // Zwalnianie pamięci
    cleanupStructures();
  }

  file.close();
}
