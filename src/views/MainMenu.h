//
// Created by jpsantos on 17-12-2023.
//

#ifndef PROJECT_AED_AIRPORTS_MAINMENU_H
#define PROJECT_AED_AIRPORTS_MAINMENU_H

#include "Menu.h"
#include "FlightTest.h" // Include the FlightTest header file
#include <iostream>
#include "utils/Dataset.h"

class MainMenu : public Menu {
public:
    void display() override {
        system("clear");
        cout << "Welcome to AED Airports!" << endl;
        // Add a new option for the flight test
        cout << "1. Flight Test\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        // If the flight test option is selected, create a new FlightTest object and call its display method
        if (choice == 1) {
            FlightTest flightTest;
            flightTest.display();
        }
    }
};

#endif //PROJECT_AED_AIRPORTS_MAINMENU_H