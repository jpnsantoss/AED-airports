//
// Created by Maureen Ah-shu🍩 on 27/12/2023.
//

#include "StatisticsMenu.h"
#include "MainMenu.h"

void StatisticsMenu::flightsOutAirport() {
    string code;
    std::cout << "Enter airport code: ";
    cin >> code;
}

void StatisticsMenu::flightsPerCity() {
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
                break;
            }
            case 2: {
                string name;
                std::cout << "Enter the name of the city: ";
                cin >> name;
                break;
            }
            default: std::cout << "Invalid option, please try again: ";
        }
    } while(option != 1 && option != 2);
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
                break;
            }
            case 2: {
                string name;
                std::cout << "Enter the name of the city: ";
                cin >> name;
                break;
            }
            default: std::cout << "Invalid option, please try again: ";
        }
    } while(option != 1 && option != 2);
}

void StatisticsMenu::backToMain() {
    MainMenu mainMenu;
    mainMenu.display();
}