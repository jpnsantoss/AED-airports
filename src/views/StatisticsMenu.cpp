//
// Created by Maureen Ah-shu🍩 on 27/12/2023.
//

#include "StatisticsMenu.h"
#include "MainMenu.h"
#include "controllers/FlightController.h"
#include "controllers/StatisticsController.h"
#include <set>

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

void StatisticsMenu::essentialAirports() {
    StatisticsController statisticsController;
    unordered_set<Airport> essentialAirports = statisticsController.findEssentialAirports();
    std::cout << "\n***********************************************************\n";
    std::cout << "\n Number of essential airports: " << essentialAirports.size() << endl;
    std::cout << endl;
    for(const Airport& a: essentialAirports){
        std::cout << " - " << a.getAirportCode() << ";\t" << a.getAirportName() << " - " << a.getCity() << endl;
    }
    printFooterOption();
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
    while(!(std::cin >> option) || option != 0) {
        std::cin.clear(); // clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the invalid input
        std::cout << "Invalid option, please try again: ";
    }
    this->display();
}