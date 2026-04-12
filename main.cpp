#include "Menu.hpp"
#include "Tester.hpp"

using namespace std;

int main() {
  Menu menu;
  Tester tester;
  int choice;

  cout << "1. Tryb pracy z menu\n"
          "2. Tryb automatycznych testow\n"
          "Ktory tryb pracy chcesz wybrac: ";
  cin >> choice;
  switch (choice) {
  case 1:
    menu.menu();
    break;
  case 2:
    tester.run("wyniki_testow.csv");
    break;
  default:
    cout << "Podano zla wartosc\n\n";
    break;
  }

  return 0;
}
