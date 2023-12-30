//
// Created by jpsantos on 17-12-2023.
//

#ifndef PROJECT_AED_AIRPORTS_MAINMENU_H
#define PROJECT_AED_AIRPORTS_MAINMENU_H

#include "Menu.h"
#include "BestOption.h" // Include the BestOption header file
#include "StatisticsMenu.h"
#include <iostream>
#include "utils/Dataset.h"

class MainMenu : public Menu {
public:
    void display() override {
        system("clear");
        std::cout << "**********************************************\n"
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
        while(!(std::cin >> option) || (option != 0 && option != 1 && option != 2)) {
            std::cin.clear(); // clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the invalid input
            std::cout << "Invalid option, please try again: ";
        }
        switch(option) {
            case 1: {
                StatisticsMenu statisticsMenu;
                statisticsMenu.display();
                break;
            }
            case 2: {
                BestOption flightTest;
                flightTest.display();
                break;
            }
            case 0: exit(0);
        }
    }
};

#endif //PROJECT_AED_AIRPORTS_MAINMENU_H