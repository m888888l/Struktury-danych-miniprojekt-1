#include "Menu.hpp"
#include "Tester.hpp"

using namespace std;

int main() {
  Menu menu;
  Tester tester;
  int choice;

  cout << "1. Tryb pracy z menu\n"
          "2. Tryb automatycznych testów\n"
          "Który tryb pracy chcesz wybrać: ";
  cin >> choice;
  switch (choice) {
  case 1:
    menu.menu();
    break;
  case 2:
    tester.run("wyniki_testow.csv");
    break;
  default:
    cout << "Podano złą wartość\n\n";
    break;
  }

  return 0;
}
