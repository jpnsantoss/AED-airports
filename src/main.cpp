#include <iostream>
#include "views/MainMenu.h"
#include "utils/Dataset.h"
int main() {
    Dataset* dataset = Dataset::getInstance();
    Menu* menu;
    // Point to main menu
    menu = new MainMenu();
    menu->display();

    return 0;
}
