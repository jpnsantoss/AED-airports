//
// Created by jpsantos on 17-12-2023.
//

#ifndef PROJECT_AED_AIRPORTS_MAINMENU_H
#define PROJECT_AED_AIRPORTS_MAINMENU_H
#include "Menu.h"
#include <iostream>
#include "utils/Dataset.h"
class MainMenu : public Menu {
public:
    void display() override {
        Dataset* dataset = Dataset::getInstance();
        cout << "Welcome to AED Airports!" << endl;

        cout << dataset->getAirlines().size() << endl;
        cout << dataset->getAirports().size() << endl;
        cout << dataset->getFlights().size() << endl;

    }
};

#endif //PROJECT_AED_AIRPORTS_MAINMENU_H
