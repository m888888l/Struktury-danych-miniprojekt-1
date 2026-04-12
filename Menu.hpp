#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "DoublyLinkedList.h"
#include "DynamicArray.h"
#include "SinglyLinkedList.h"

using namespace std;

class Menu {
public:
  void menu();

private:
  int action;
  int value;
  int index;
  void takeAction(int dataStructure);
  void generateRandom(int structure, int size, int seed);
  void loadFromFile(string fileName, char separator, int structure);
  DynamicArray *d_array = new DynamicArray(5);
  SinglyLinkedList *sl_list = new SinglyLinkedList();
  DoublyLinkedList *dl_list = new DoublyLinkedList();
};

void Menu::menu() {
  while (1) {
    system("cls");
    action = 0;
    // Wybór struktury
    cout << "\n1. Tablica dynamiczna\n"
            "2. Lista jednokierunkowa\n"
            "3. Lista dwukierunkowa\n"
            "4. Wyjdz\n"
            "Ktora strukture chcesz edytowac: ";
    cin >> action;

    // W zależności od wyboru odesłanie do odpowiedniego fragmentu kodu
    if (action > 0 && action < 4) takeAction(action);
    else if (action == 4){
      delete d_array;
      delete sl_list;
      delete dl_list;

      return;
    }
    else cout << "\nPodano zla wartosc";
  }
}

void Menu::generateRandom(int structure, int size, int seed) {
  srand(seed);
  if(structure == 1) { 
    delete d_array;
    d_array = new DynamicArray(size);
    for(int i = 0; i < size; i++) d_array->push_back(rand());
  }
  else if(structure == 2) { 
    delete sl_list;
    sl_list = new SinglyLinkedList;
    for(int i = 0; i < size; i++) sl_list->push_back(rand());
  }
  else{ 
    delete dl_list;
    dl_list = new DoublyLinkedList;
    for(int i = 0; i < size; i++) dl_list->push_back(rand());
  }
}

void Menu::loadFromFile(string fileName, char separator, int structure) {
  ifstream file(fileName);
  if (!file.is_open())
      return;

  string line;

  if(structure == 1) { 
    delete d_array;
    d_array = new DynamicArray(5);
  }
  else if(structure == 2) { 
    delete sl_list;
    sl_list = new SinglyLinkedList;
  }
  else{ 
    delete dl_list;
    dl_list = new DoublyLinkedList;
  }

  while (getline(file, line))
  {
    stringstream ss(line);
    string token;

    while (getline(ss, token, separator))
    {
      if (!token.empty())
      {
        if(structure == 1) d_array->push_back(stoi(token));
        else if(structure == 2) sl_list->push_back(stoi(token)); 
        else dl_list->push_back(stoi(token)); 
      }
    }
  }
}

void Menu::takeAction(int dataStructure) {
  // Zerowanie wyborów aby przeciwdziałać błędom
  while(1){
    action = 0;
    value = 0;
    index = 0;
    system("cls");
    cout << "\n";

    // Wyświetlanie struktury dla ułatwienia operacji
    if (dataStructure == 1) {
      d_array->print();
    } else if (dataStructure == 2) {
      sl_list->print();
    } else {
      dl_list->print();
    }
    // Pyta o akcje i wysyla do odpowiedniej struktury
    cout << "\n1. Dodaj element na poczatek struktury\n"
            "2. Usun element z poczatku struktury\n"
            "3. Dodaj element na koniec struktury\n"
            "4. Usun element z konca struktury\n"
            "5. Dodaj element do wybranego miejsca\n"
            "6. Usun element z wybranego miejsca\n"
            "7. Wygeneruj losowe wartosci\n"
            "8. Zaladuj wartosci z pliku\n"
            "9. Wyjdz\n"
            "Co chcesz zrobic: ";
            
    cin >> action;
    system("cls");
    // Jeśli to konieczne to pyta o wartość i index
    if (action == 9) return;
    if (action == 1 || action == 3 || action == 5) {
      cout << "\nJaki element chcesz dodac: ";
      cin >> value;
    }
    if (action == 5 || action == 6) {
      cout << "\nWybierz index: ";
      cin >> index;
    }
    else if(action == 7){
      int size;
      int seed;
      cout<<"\nIle losowych wartosci chcesz wygenerowac: ";
      cin>>size;
      cout<<"Jakiego seeda chcesz uzyc: ";
      cin>>seed;
      generateRandom(dataStructure, size, seed);
    }
    else if(action == 8){
      string fileName;
      char separator;
      cout<<"Z jakiego pliku chcesz zaladowac dane: ";
      cin>>fileName;
      cout<<"Jaki separator jest uzyty w pliku: ";
      cin>>separator;
      loadFromFile(fileName, separator, dataStructure);
    }

    // Odsyłanie do odpowiedniej metody
    switch (action) {
    case 1:
      if (dataStructure == 1) {
        d_array->insert(0, value);
      } else if (dataStructure == 2) {
        sl_list->push_front(value);
      } else {
        dl_list->push_front(value);
      }
      break;
    case 2:
      if (dataStructure == 1) {
        d_array->pop_at(0);
      } else if (dataStructure == 2) {
        sl_list->pop_front();
      } else {
        dl_list->pop_front();
      }
      break;
    case 3:
      if (dataStructure == 1) {
        d_array->push_back(value);
      } else if (dataStructure == 2) {
        sl_list->push_back(value);
      } else {
        dl_list->push_back(value);
      }
      break;
    case 4:
      if (dataStructure == 1) {
        d_array->pop_back();
      } else if (dataStructure == 2) {
        sl_list->pop_back();
      } else {
        dl_list->pop_back();
      }
      break;
    case 5:
      if (dataStructure == 1) {
        d_array->insert(index, value);
      } else if (dataStructure == 2) {
        sl_list->insert(index, value);
      } else {
        dl_list->insert(index, value);
      }
      break;
    case 6:
      if (dataStructure == 1) {
        d_array->pop_at(index);
      } else if (dataStructure == 2) {
        sl_list->pop_at(index);
      } else {
        dl_list->pop_at(index);
      }
      break;
    default:
      cout << "Podano zla wartosc\n" << endl;
      break;
    }
  }
}
