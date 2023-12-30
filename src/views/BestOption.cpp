#include "BestOption.h"
#include "MainMenu.h"

/**
 * Displays the best flight options to the user.
 * Complexity: O(n), where n is the number of paths.
 * @brief This function is the main loop for the BestOption menu. It repeatedly prompts the user to select a filter, source, and destination for the flight search,
 * then displays the best flight options based on the user's selections. The user is then asked if they want to search another flight.
 * If the user chooses to search another flight, the function continues to the next iteration of the loop. If the user chooses to go back to the main menu, the function returns.
 * @see selectFilter(), selectSource(), selectDestination(), displayPaths(), MainMenu::backToMain()
 * @return void
 */
void BestOption::display() {
    while (true) {
        system("clear");

        BestOptionController* optionController = selectFilter();
        if (!optionController) {
            return;
        }

        auto [sourceOption, source] = selectSource();
        if (sourceOption == FlightOption::INVALID) {
            return;
        }

        auto [destinationOption, destination] = selectDestination();
        if (destinationOption == FlightOption::INVALID) {
            return;
        }

        system("clear");
        displayPaths(optionController->getBestFlightOption(sourceOption, source, destinationOption, destination));

        int choice;
        cout << "Do you want to search another flight? (1 for yes, 0 for no): ";
        cin >> choice;
        if (choice == 0) {
            MainMenu::backToMain();
            return;
        }
    }
}
/**
 * Prints the source menu to the console.
 * Complexity: O(1), as the number of menu options is fixed.
 * @brief Prints the source menu and prompts the user to enter an option.
 * @return void
 */
void BestOption::printSourceMenu() {
    cout << "**********************************************\n"
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

/**
 * Prints the destination menu to the console.
 * Complexity: O(1), as the number of menu options is fixed.
 * @brief Prints the destination menu and prompts the user to enter an option.
 * @return void
 */
void BestOption::printDestinationMenu() {
    cout << "**********************************************\n"
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

/**
 * Prompts the user to select a filter for the flight search.
 * Complexity: O(1), as the number of filter options is fixed.
 * @brief Displays the filter menu and handles user input for the filter options.
 * @see MainMenu::backToMain(), AirlineFilterController::AirlineFilterController(), MinimizeAirlinesController::MinimizeAirlinesController(), BestOptionController::BestOptionController()
 * @return A pointer to a BestOptionController object that applies the selected filter, or nullptr if the user chooses to go back to the main menu.
 */
BestOptionController* BestOption::selectFilter() {
    int filterChoice;
    cout << "**********************************************\n"
              << "*   best flight option                       *\n"
              << "*                                            *\n"
              << "*     Do you want to add any filter?         *\n"
              << "*                                            *\n"
              << "*     1) Yes                                 *\n"
              << "*     2) No                                  *\n"
              << "*                                            *\n"
              << "*                                   0) Back  *\n"
              << "**********************************************\n"
              << "Option: ";
    cin >> filterChoice;

    switch (filterChoice) {
        case 0:
            MainMenu::backToMain();
            return nullptr;
        case 1: {
            cout << "**********************************************\n"
                      << "*   best flight option                       *\n"
                      << "*                                            *\n"
                      << "*           Choose filter option             *\n"
                      << "*                                            *\n"
                      << "*     1) Airline filter                      *\n"
                      << "*     2) Minimize airlines filter            *\n"
                      << "*                                            *\n"
                      << "*                                   0) Back  *\n"
                      << "**********************************************\n"
                      << "Option: ";
            cin >> filterChoice;

            switch (filterChoice) {
                case 0:
                    MainMenu::backToMain();
                    return nullptr;
                case 1: {
                    system("clear");
                    vector<string> airlines;
                    string airline;
                    cout << "Enter airlines (type 'done' when finished): ";
                    while (cin >> airline && airline != "done") {
                        airlines.push_back(airline);
                    }
                    cout << "Generating new graph...\n";
                    return new AirlineFilterController(airlines);
                }
                case 2:
                    return new MinimizeAirlinesController();
                default:
                    cout << "Invalid choice. Please try again.\n";
                    return nullptr;
            }
        }
        case 2:
            return new BestOptionController();
        default:
            cout << "Invalid choice. Please try again.\n";
            return nullptr;
    }
}

/**
 * Prompts the user to select the source airport for the flight search.
 * Complexity: O(1), as the number of source options is fixed.
 * @brief Displays the source menu and handles user input for the source options.
 * @see MainMenu::backToMain()
 * @return A pair consisting of a FlightOption enumerator representing the source option and a string representing the source airport code, airport name, city, or location, depending on the source option. If the user chooses to go back to the main menu, the function returns a pair with FlightOption::INVALID and an empty string.
 */
pair<FlightOption, string> BestOption::selectSource() {
    int sourceChoice;
    double sourceLat, sourceLon;
    string source;

    printSourceMenu();
    cout << "Option: ";
    cin >> sourceChoice;

    switch (sourceChoice) {
        case 0:
            MainMenu::backToMain();
            return {FlightOption::INVALID, ""};
        case 1:
            cout << "Enter source airport code: ";
            cin >> source;
            break;

        case 2:
            cout << "Enter source airport name: ";
            cin >> source;
            break;
        case 3:
            cout << "Enter source city: ";
            cin >> source;
            break;
        case 4:
            cout << "Enter latitude for source location: ";
            cin >> sourceLat;
            cout << "Enter longitude for source location: ";
            cin >> sourceLon;
            source = to_string(sourceLat) + "," + to_string(sourceLon);
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            return {FlightOption::INVALID, ""};
    }

    return {static_cast<FlightOption>(sourceChoice - 1), source};
}

/**
 * Prompts the user to select the destination airport for the flight search.
 * Complexity: O(1), as the number of destination options is fixed.
 * @brief Displays the destination menu and handles user input for the destination options.
 * @see MainMenu::backToMain()
 * @return A pair consisting of a FlightOption enumerator representing the destination option and a string representing the destination airport code, airport name, city, or location, depending on the destination option. If the user chooses to go back to the main menu, the function returns a pair with FlightOption::INVALID and an empty string.
 */
pair<FlightOption, string> BestOption::selectDestination() {
    int destinationChoice;
    double destLat, destLon;
    string destination;

    printDestinationMenu();
    cin >> destinationChoice;

    switch (destinationChoice) {
        case 0:
            MainMenu::backToMain();
            return {FlightOption::INVALID, ""};
        case 1:
            cout << "Enter destination airport code: ";
            cin >> destination;
            break;
        case 2:
            cout << "Enter destination airport name: ";
            cin >> destination;
            break;
        case 3:
            cout << "Enter destination city: ";
            cin >> destination;
            break;
        case 4:
            cout << "Enter latitude for destination location: ";
            cin >> destLat;
            cout << "Enter longitude for destination location: ";
            cin >> destLon;
            destination = to_string(destLat) + "," + to_string(destLon);
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            return {FlightOption::INVALID, ""};
    }

    return {static_cast<FlightOption>(destinationChoice - 1), destination};
}

/**
 * Displays the possible flight paths to the user.
 * Complexity: O(n), where n is the number of paths.
 * @brief Iterates over each path and for each path, it iterates over each airport in the path.
 * It then finds the flight from the current airport to the next airport, gets the airline from the flight,
 * and displays the airline in the middle of the arrow between each pair of airports.
 * @see Dataset::getInstance(), Dataset::findFlight()
 * @param paths - A vector of vectors, each representing one of the best flight options.
 * @return void
 */
void BestOption::displayPaths(const vector<vector<Airport>>& paths) {
    if (paths.empty()) {
        cout << "\n**********************************************\n"
                  << "*   No path found                            *\n"
                  << "**********************************************\n";
    } else {
        cout << "\n**********************************************\n"
             << "*   Possible paths:                          *\n"
             << "**********************************************\n";
        for (const auto& path : paths) {
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i].getAirportName() << " (" << path[i].getCity() << ")";
                if (i != path.size() - 1) {
                    // Get the flight from the current airport to the next airport
                    Flight* flight = Dataset::getInstance()->findFlight(path[i], path[i+1]);
                    if (flight != nullptr) {
                        // Get the airline from the flight
                        Airline airline = flight->getAirline();
                        // Display the airline in the middle of the arrow
                        cout << " --[" << airline.getName() << "]--> ";
                    }
                }
            }
            cout << "\n";
        }
        cout << "**********************************************\n";
    }
}