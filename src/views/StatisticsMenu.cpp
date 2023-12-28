//
// Created by Maureen Ah-shu🍩 on 27/12/2023.
//

#include "StatisticsMenu.h"
#include "MainMenu.h"
#include "controllers/FlightController.h"
#include <set>

void StatisticsMenu::flightsOutAirport() {
    string code;
    FlightController controller;
    std::cout << "Enter airport code: ";
    cin >> code;
    set<Airline> airlines = controller.setOfFlightsOutAirport(code);
    std::cout << "\n***********************************************************\n";
    std::cout << "Number of flights out of this airport: " << controller.numberOfFlightsOutAirport(code) << endl;
    std::cout << "Number of airlines that flight out of this airport: " << airlines.size() << endl;
    std::cout << endl;
    for(const Airline& air: airlines){
        std::cout << " - " << air.getCode() << ";\t" << air.getName() << " - " << air.getCountry() << endl;
    }
    printFooterOption();
}

void StatisticsMenu::flightsPerCityAirline() {
    int option;
    FlightController controller;
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
                std::cout << "\n - Number of flights made by this airline: " << controller.numberOfFlightsPerAirline(code) << endl;
                break;
            }
            case 2: {
                string name;
                std::cout << "Enter the name of the city: ";
                cin >> name;
                std::cout << "\n***********************************************************\n";
                std::cout << "\n - Number of flights in this city: " << controller.numberOfFlightsPerCity(name) << endl;
                break;
            }
            default: std::cout << "Invalid option, please try again: ";
        }
    } while(option != 1 && option != 2);
    printFooterOption();
}

void StatisticsMenu::airportToCountries() {
    int option;
    FlightController controller;
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
                set<string> countries = controller.numberOfCountriesForThisAirport(code);
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
                set<string> countries = controller.numberOfCountriesForThisCity(name);
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