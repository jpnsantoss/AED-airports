// BestOption.h
#ifndef PROJECT_AED_AIRPORTS_BESTOPTION_H
#define PROJECT_AED_AIRPORTS_BESTOPTION_H

#include "Menu.h"
#include "controllers/FlightController.h"
#include "controllers/filters/AirlineFilterFlightController.h"
#include "controllers/filters/MinimizeAirlinesFlightController.h"
#include <iostream>
#include <vector>
#include <limits>

class BestOption : public Menu {
public:
    void display() override {
        system("clear");
        FlightController* flightController = nullptr;
        int filterChoice;
        std::cout << "Before we start, do you want to add any filter to your search? (1 for yes, 2 for no): ";
        std::cin >> filterChoice;

        if (filterChoice == 1) {
            std::cout << "Choose filter option:\n";
            std::cout << "1. Airline filter\n";
            std::cout << "2. Minimize airlines filter\n";
            std::cout << "Enter your choice: ";
            std::cin >> filterChoice;

            switch (filterChoice) {
                case 1: {
                    system("clear");
                    std::vector<std::string> airlines;
                    std::string airline;
                    std::cout << "Enter airlines (type 'done' when finished): ";
                    while (std::cin >> airline && airline != "done") {
                        airlines.push_back(airline);
                    }
                    cout << "Generating new graph...\n";
                    flightController = new AirlineFilterFlightController(airlines);
                    break;
                }
                case 2:
                    flightController = new MinimizeAirlinesFlightController();
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    return;
            }
        }
        else if (filterChoice == 2) {
            flightController = new FlightController();
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
            return;
        }

        int sourceChoice, destinationChoice;
        std::string source, destination;
        double sourceLat, sourceLon, destLat, destLon;

        while (true) {
            system("clear");
            printSourceMenu();
            std::cin >> sourceChoice;

            switch (sourceChoice) {
                case 1:
                case 2:
                    std::cout << "Enter source airport code: ";
                    std::cin >> source;
                    break;
                case 3:
                    std::cout << "Enter source city: ";
                    std::cin >> source;
                    break;
                case 4:
                    std::cout << "Enter latitude for source location: ";
                    std::cin >> sourceLat;
                    std::cout << "Enter longitude for source location: ";
                    std::cin >> sourceLon;
                    source = to_string(sourceLat) + "," + to_string(sourceLon);
                    break;
                case 0:
                    return;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    continue;
            }
            system("clear");
            printDestinationMenu();
            std::cin >> destinationChoice;

            switch (destinationChoice) {
                case 1:
                case 2:
                    std::cout << "Enter destination airport name: ";
                    std::cin >> destination;
                    break;
                case 3:
                    std::cout << "Enter destination city: ";
                    std::cin >> destination;
                    break;
                case 4:
                    std::cout << "Enter latitude for destination location: ";
                    std::cin >> destLat;
                    std::cout << "Enter longitude for destination location: ";
                    std::cin >> destLon;
                    destination = to_string(destLat) + "," + to_string(destLon);
                    break;
                case 0:
                    return;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                    continue;
            }
            system("clear");
            FlightOption sourceOption = static_cast<FlightOption>(sourceChoice - 1);
            FlightOption destinationOption = static_cast<FlightOption>(destinationChoice - 1);
            displayPaths(flightController->getBestFlightOption(sourceOption, source, destinationOption, destination));
            std::cout << "Press enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }

private:
    void printSourceMenu() {
        std::cout << "**********************************************\n"
                  << "*   best flight option                       *\n"
                  << "*                                            *\n"
                  << "*           Choose source option             *\n"
                  << "*                                            *\n"
                  << "*     1) By airport code                     *\n"
                  << "*     2) By airport name                     *\n"
                  << "*     3) By city                             *\n"
                  << "*     4) By location                         *\n"
                  << "*                                            *\n"
                  << "*                                   0) Back  *\n"
                  << "**********************************************\n"
                  << "Option: ";
    }

    void printDestinationMenu() {
        std::cout << "**********************************************\n"
                  << "*   best flight option                       *\n"
                  << "*                                            *\n"
                  << "*         Choose destination option          *\n"
                  << "*                                            *\n"
                  << "*     1) By airport code                     *\n"
                  << "*     2) By airport name                     *\n"
                  << "*     3) By city                             *\n"
                  << "*     4) By location                         *\n"
                  << "*                                            *\n"
                  << "*                                   0) Back  *\n"
                  << "**********************************************\n"
                  << "Option: ";
    }

    void displayPaths(const std::vector<std::vector<Airport>>& paths) {
        if (paths.empty()) {
            std::cout << "No path found\n";
        } else {
            cout << "Possible paths:\n";
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

#endif //PROJECT_AED_AIRPORTS_BESTOPTION_H