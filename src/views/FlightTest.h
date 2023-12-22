// FlightTest.h
#ifndef PROJECT_AED_AIRPORTS_FLIGHTTEST_H
#define PROJECT_AED_AIRPORTS_FLIGHTTEST_H

#include "Menu.h"
#include "controllers/FlightController.h"
#include <iostream>
#include <vector>

class FlightTest : public Menu {
public:
    void display() override {
        FlightController flightController;
        int choice;
        std::string source, destination;

        while (true) {
            printMenu();
            std::cin >> choice;

            switch (choice) {
                case 1:
                    std::cout << "Enter source airport: ";
                    std::cin >> source;
                    std::cout << "Enter destination airport: ";
                    std::cin >> destination;
                    displayPaths(flightController.getBestFlightOptionByAirport(source, destination));
                    break;
                case 2:
                    std::cout << "Enter source city: ";
                    std::cin >> source;
                    std::cout << "Enter destination city: ";
                    std::cin >> destination;
                    displayPaths(flightController.getBestFlightOptionByCity(source, destination));
                    break;
                case 3:
                    return;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }

private:
    void printMenu() {
        std::cout << "1. Find best flight option by airport\n";
        std::cout << "2. Find best flight option by city\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
    }

    void displayPaths(const std::vector<std::vector<Airport>>& paths) {
        if (paths.empty()) {
            std::cout << "No path found\n";
        } else {
            for (const auto& path : paths) {
                for (size_t i = 0; i < path.size(); ++i) {
                    std::cout << path[i].getAirportName() << " (" << path[i].getCity() << ")";
                    if (i != path.size() - 1) {
                        std::cout << " -> ";
                    }
                }
                std::cout << "\n";
            }
        }
    }
};

#endif //PROJECT_AED_AIRPORTS_FLIGHTTEST_H