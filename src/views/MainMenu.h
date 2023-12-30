
#ifndef PROJECT_AED_AIRPORTS_MAINMENU_H
#define PROJECT_AED_AIRPORTS_MAINMENU_H

#include <iostream>

#include "Menu.h"
#include "StatisticsMenu.h"
#include "utils/Dataset.h"

using namespace std;

class MainMenu : public Menu {
public:
    void display() override;
    static void backToMain(); // Add this line
};
#endif //PROJECT_AED_AIRPORTS_MAINMENU_H