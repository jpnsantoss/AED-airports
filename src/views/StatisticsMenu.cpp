
#include "StatisticsMenu.h"
#include "MainMenu.h"
#include "controllers/FlightController.h"
#include "controllers/StatisticsController.h"
#include <set>

void StatisticsMenu::numberAirportsFlights() {
    std::cout << "\n***********************************************************\n"
              << "Global number of airports: " << StatisticsController::getTotalAirports() << "\n"
              << "Global number of available flights: " << StatisticsController::getTotalFlights() << endl;
    printFooterOption();
}

void StatisticsMenu::flightsOutAirport() {
    string code;
    std::cout << "Enter airport code: ";
    cin >> code;
    set<Airline> airlines = StatisticsController::setOfFlightsOutAirport(code);
    std::cout << "\n***********************************************************\n";
    std::cout << "Number of flights out of this airport: " << StatisticsController::numberOfFlightsOutAirport(code) << endl;
    std::cout << "Number of airlines that flight out of this airport: " << airlines.size() << endl;
    std::cout << endl;
    for(const Airline& air: airlines){
        std::cout << " - " << air.getCode() << ";\t" << air.getName() << " - " << air.getCountry() << endl;
    }
    printFooterOption();
}

void StatisticsMenu::flightsPerCityAirline() {
    int option;
    std::cout << "Choose an option:\n";
    std::cout << "1) Airline \n";
    std::cout << "2) City \n";
    std::cout << "Option: ";
    do{
        std::cin >> option;
        switch(option) {
            case 1: {
                string code;
                std::cout << "Enter airline code: ";
                cin >> code;
                std::cout << "\n***********************************************************\n";
                std::cout << "\n - Number of flights made by this airline: " << StatisticsController::numberOfFlightsPerAirline(code) << endl;
                break;
            }
            case 2: {
                string name;
                std::cout << "Enter the name of the city: ";
                cin >> name;
                std::cout << "\n***********************************************************\n";
                std::cout << "\n - Number of flights in this city: " << StatisticsController::numberOfFlightsPerCity(name) << endl;
                break;
            }
            default: std::cout << "Invalid option, please try again: ";
        }
    } while(option != 1 && option != 2);
    printFooterOption();
}

void StatisticsMenu::airportToCountries() {
    int option;
    std::cout << "Choose an option:\n";
    std::cout << "1) Airport \n";
    std::cout << "2) City \n";
    std::cout << "Option: ";
    do{
        std::cin >> option;
        switch(option) {
            case 1: {
                string code;
                std::cout << "Enter airport code: ";
                cin >> code;
                set<string> countries = StatisticsController::numberOfCountriesForThisAirport(code);
                std::cout << "\n***********************************************************\n";
                std::cout << "\n Number of countries this airport flies to: " << countries.size() << endl;
                std::cout << endl;
                for(const string& c: countries){
                    std::cout << " - " << c << "\n";
                }
                break;
            }
            case 2: {
                string name;
                std::cout << "Enter the name of the city: ";
                cin >> name;
                set<string> countries = StatisticsController::numberOfCountriesForThisCity(name);
                std::cout << "\n***********************************************************\n";
                std::cout << "\n Number of countries this city flies to: " << countries.size() << endl;
                std::cout << endl;
                for(const string& c: countries){
                    std::cout << " - " << c << "\n";
                }
                break;
            }
            default: std::cout << "Invalid option, please try again: ";
        }
    } while(option != 1 && option != 2);
    printFooterOption();
}

void StatisticsMenu::numberDestinations() {
    StatisticsController controller;
    string code;
    std::cout << "For which airport are you inquiring about the number of destinations available?\n"
              << "Enter airport code:";
    cin >> code;
    int option;
    std::cout << "Choose an option:\n"
              << "1) Airports \n"
              << "2) Countries \n"
              << "3) Cities \n"
              << "Option: ";
    do {
        std::cin >> option;
        switch (option) {
            case 1: {
                std::cout << "\n***********************************************************\n"
                          << "\n Number of airports available: " << controller.getNumberOfDestinationAirports(code) << endl;
                break;
            }
            case 2: {
                std::cout << "\n***********************************************************\n"
                          << "\n Number of countries available: " << controller.getNumberOfDestinationCountries(code) << endl;
                break;
            }
            case 3: {
                std::cout << "\n***********************************************************\n"
                          << "\n Number of cities available: " << controller.getNumberOfDestinationCities(code) << endl;
                break;
            }
            default: std::cout << "Invalid option, please try again: ";
        }
    } while (option != 1 && option != 2 && option != 3);
    printFooterOption();
}

void StatisticsMenu::numberDestinationXstops() {
    StatisticsController controller;
    string code;
    std::cout << "For which airport are you inquiring about the number of destinations available?\n"
              << "Enter airport code:";
    cin >> code;
    int stops;
    std::cout << "How many stops? ";
    cin >> stops;
    int option;
    std::cout << "Choose an option:\n"
              << "1) Airports \n"
              << "2) Countries \n"
              << "3) Cities \n"
              << "Option: ";
    do {
        std::cin >> option;
        switch (option) {
            case 1: {
                std::cout << "\n***********************************************************\n"
                          << "\n Number of airports available: " << controller.getNumberOfReachableAirportsWithMaxStops(code, stops) << endl;
                break;
            }
            case 2: {
                std::cout << "\n***********************************************************\n"
                          << "\n Number of countries available: " << controller.getNumberOfReachableCountriesWithMaxStops(code, stops) << endl;
                break;
            }
            case 3: {
                std::cout << "\n***********************************************************\n"
                          << "\n Number of cities available: " << controller.getNumberOfReachableCitiesWithMaxStops(code, stops) << endl;
                break;
            }
            default: std::cout << "Invalid option, please try again: ";
        }
    } while (option != 1 && option != 2 && option != 3);
    printFooterOption();
}

void StatisticsMenu::maxTrip() {

}

void StatisticsMenu::backToMain() {
    MainMenu mainMenu;
    mainMenu.display();
}

void StatisticsMenu::printFooterOption(){
    int option;
    std::cout << "\n                                                   0) Back   "
              << "\n***********************************************************\n"
              << "Option: ";
    do {
        std::cin >> option;
        if (option != 0)
            std::cout << "Invalid option, please try again: ";
        else
            this->display();
    } while (option != 0);
}