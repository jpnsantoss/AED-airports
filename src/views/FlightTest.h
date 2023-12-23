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
        double sourceLat, sourceLon, destLat, destLon;

        while (true) {
            printMenu();
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    std::cout << "Enter source airport: ";
                    std::cin >> source;
                    std::cout << "Enter destination airport: ";
                    std::cin >> destination;
                    displayPaths(flightController.getBestFlightOptionByAirport(source, destination));
                    break;
                }
                case 2: {
                    std::cout << "Enter source city: ";
                    std::cin >> source;
                    std::cout << "Enter destination city: ";
                    std::cin >> destination;
                    displayPaths(flightController.getBestFlightOptionByCity(source, destination));
                    break;
                }
                case 3: {
                    std::cout << "Enter latitude for source location: ";
                    std::cin >> sourceLat;
                    std::cout << "Enter longitude for source location: ";
                    std::cin >> sourceLon;
                    std::cout << "Enter latitude for destination location: ";
                    std::cin >> destLat;
                    std::cout << "Enter longitude for destination location: ";
                    std::cin >> destLon;
                    Location sourceLocation(sourceLat, sourceLon);
                    Location destinationLocation(destLat, destLon);
                    displayPaths(flightController.getBestFlightOptionByLocation(sourceLocation, destinationLocation));
                    break;
                }
                case 4:
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
        std::cout << "3. Find best flight option by location\n";
        std::cout << "4. Exit\n";
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