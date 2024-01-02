
#include "MainMenu.h"
#include "BestOption.h"

void MainMenu::display() {
    system("clear");
    cout << "**********************************************\n"
              << "*                                            *\n"
              << "*         Welcome to AED Airports            *\n"
              << "*                                            *\n"
              << "*     1) NETWORK STATISTICS                  *\n"
              << "*     2) BEST FLIGHT OPTION                  *\n"
              << "*     0) EXIT                                *\n"
              << "*                                            *\n"
              << "**********************************************\n"
              << "Option: ";
    int option;
    while(!(cin >> option) || (option != 0 && option != 1 && option != 2)) {
        cin.clear(); // clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the invalid input
        cout << "Invalid option, please try again: ";
    }
    switch(option) {
        case 1: {
            StatisticsMenu statisticsMenu;
            statisticsMenu.display();
            break;
        }
        case 2: {
            BestOption bestOption;
            bestOption.display();
            break;
        }
        case 0: exit(0);
    }
}

void MainMenu::backToMain() {
    system("clear");
    MainMenu mainMenu;
    mainMenu.display();
}