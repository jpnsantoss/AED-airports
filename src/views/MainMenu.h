//
// Created by jpsantos on 17-12-2023.
//

#ifndef PROJECT_AED_AIRPORTS_MAINMENU_H
#define PROJECT_AED_AIRPORTS_MAINMENU_H

#include "Menu.h"
#include "FlightTest.h" // Include the FlightTest header file
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
                  << "*     3) BEST FLIGHT OPTION WITH FILTERS     *\n"
                  << "*     0) EXIT                                *\n"
                  << "*                                            *\n"
                  << "**********************************************\n"
                  << "Option: ";
        int option;
        do{
            std::cin >> option;
            switch(option) {
                case 1: {
                    StatisticsMenu statisticsMenu;
                    statisticsMenu.display();
                    break;
                }
                case 2: {
                    FlightTest flightTest;
                    flightTest.display();
                    break;
                }
                case 3: {
                    break;
                }
                case 0: exit(0);
                default: std::cout << "Invalid option, please try again: ";
            }
        } while(option != 0 && option != 1 && option != 2 && option != 3);
    }
};

#endif //PROJECT_AED_AIRPORTS_MAINMENU_H