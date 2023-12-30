#include <iostream>
#include "views/MainMenu.h"
#include "utils/Dataset.h"

/**
* Entry point of the application.
* Complexity: Depends on the complexity of the functions called within.
* @brief Loads the dataset, initializes the main menu, and starts the menu display loop.
* @see Dataset::getInstance(), MainMenu::display()
* @return 0 when the program exits successfully.
*/
int main() {
    cout << "Loading dataset..." << endl;
    Dataset* dataset = Dataset::getInstance();
    Menu* menu;
    // Point to main menu
    menu = new MainMenu();
    menu->display();

    return 0;
}
