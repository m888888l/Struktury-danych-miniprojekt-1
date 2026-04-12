#pragma once

#include <cstdlib>
#include <iostream>

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
  DynamicArray *d_array = new DynamicArray(5);
  SinglyLinkedList *sl_list = new SinglyLinkedList();
  DoublyLinkedList *dl_list = new DoublyLinkedList();
};

void Menu::menu() {
  while (1) {
    system("clear");
    action = 0;
    cout << "\n\n1. Tablica dynamiczna\n"
            "2. Lista jednokierunkowa\n"
            "3. Lista dwukierunkowa\n"
            "4. Wyjdz\n"
            "Ktora strukture chcesz edytowac: ";
    cin >> action;

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

void Menu::takeAction(int dataStructure) {
  action = 0;
  value = 0;
  index = 0;
  system("clear");
  cout << "\n";

  if (dataStructure == 1) {
    d_array->print();
  } else if (dataStructure == 2) {
    sl_list->print();
  } else {
    dl_list->print();
  }
  // Pyta o akcje i wysyla do odpowiedniej struktury
  cout << "\n\n1. Dodaj element na poczatek struktury\n"
          "2. Usun element z poczatku struktury\n"
          "3. Dodaj element na koniec struktury\n"
          "4. Usun element z konca struktury\n"
          "5. Dodaj element do wybranego miejsca\n"
          "6. Usun element z wybranego miejsca\n"
          "7. Wyjdz\n"
          "Co chcesz zrobic: ";
  cin >> action;
  system("clear");
  if (action == 7) return;
  if (action == 1 || action == 3 || action == 5) {
    cout << "\n\nJaki element chcesz dodac: ";
    cin >> value;
  }
  if (action == 5 || action == 6) {
    cout << "\n\nWybierz index: ";
    cin >> index;
  }


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
  menu();
}
