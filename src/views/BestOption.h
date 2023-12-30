#ifndef PROJECT_AED_AIRPORTS_BESTOPTION_H
#define PROJECT_AED_AIRPORTS_BESTOPTION_H

#include <iostream>
#include <vector>
#include <limits>
#include "Menu.h"
#include "controllers/FlightController.h"
#include "controllers/filters/AirlineFilterController.h"
#include "controllers/filters/MinimizeAirlinesController.h"

using namespace std;

class BestOption : public Menu {
public:
    void display() override;

private:
    void printSourceMenu();
    void printDestinationMenu();
    void displayPaths(const vector<vector<Airport>>& paths);

    BestOptionController *selectFilter();

    pair<FlightOption, string> selectSource();

    pair<FlightOption, string> selectDestination();
};

#endif //PROJECT_AED_AIRPORTS_BESTOPTION_H