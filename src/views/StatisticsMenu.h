
#ifndef PROJECT_AED_AIRPORTS_STATISTICSMENU_H
#define PROJECT_AED_AIRPORTS_STATISTICSMENU_H

#include <iostream>
#include <set>
#include <unordered_set>
#include <limits>
#include "Menu.h"
#include "models/Airline.h"

class StatisticsMenu : public Menu {
public:
    void display() override {
        std::cout << "****************************************************************************************\n"
                  << "*   network statistics                                                                 *\n"
                  << "*                                                                                      *\n"
                  << "*     1) Global number of airports and number of available flights                     *\n"
                  << "*     2) Number of flights out of an airport; and from how many different airlines     *\n"
                  << "*     3) Number of flights per city/airline                                            *\n"
                  << "*     4) Number of different countries that a given airport/city flies to              *\n"
                  << "*     5) Number of destinations (airports, cities or countries) available              *\n"
                  << "*        for a given airport                                                           *\n"
                  << "*     6) Number of reachable destinations (airports, cities or countries)              *\n"
                  << "*        from a given airport in a maximum number of X stops (lay-overs)               *\n"
                  << "*     7) Maximum trip and corresponding pair of source-destination airports            *\n"
                  << "*     8) Identify the top-k airport with the greatest air traffic capacity             *\n"
                  << "*     9) Identify the airports that are essential to the circulation capabilty         *\n"
                  << "*        of the network                                                                *\n"
                  << "*                                                                                      *\n"
                  << "*                                                                              0) Back *\n"
                  << "****************************************************************************************\n"
                  << "Option: ";
        int option;
        while(!(std::cin >> option) || (option < 0 || option > 9)) {
            std::cin.clear(); // clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the invalid input
            std::cout << "Invalid option, please try again: ";
        }
        switch(option) {
            case 1: numberAirportsFlights(); break;
            case 2: flightsOutAirport(); break;
            case 3: flightsPerCityAirline(); break;
            case 4: airportToCountries(); break;
            case 5: numberDestinations(); break;
            case 6: numberDestinationXstops(); break;
            case 7: maxTrip(); break;
            case 8: topKAirports(); break;
            case 9: essentialAirports(); break;
            case 0: backToMain(); break;
        }
    }
private:
    void numberAirportsFlights();
    void flightsOutAirport();
    void flightsPerCityAirline();
    void airportToCountries();
    void numberDestinations();
    void numberDestinationXstops();
    void maxTrip();
    void topKAirports();
    void essentialAirports();
    static void backToMain();
    void printFooterOption();
};

#endif //PROJECT_AED_AIRPORTS_STATISTICSMENU_H
