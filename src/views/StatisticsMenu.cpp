
#include "StatisticsMenu.h"
#include "MainMenu.h"
#include "controllers/FlightController.h"
#include "controllers/StatisticsController.h"


/**
 * @brief Displays the number all airports and airlines of the dataset.
 */
void StatisticsMenu::numberAirportsFlights() {
    cout << "\n***********************************************************\n"
              << "Global number of airports: " << StatisticsController::getTotalAirports() << "\n"
              << "Global number of available flights: " << StatisticsController::getTotalFlights() << endl;
    printFooterOption();
}

/**
 * @brief Displays the number of flights out of a given airport and the airlines that flight out of it.
 */
void StatisticsMenu::flightsOutAirport() {
    string code;
    StatisticsController controller;
    cout << "Enter airport code: ";
    cin >> code;
    set<Airline> airlines = controller.setOfFlightsOutAirport(code);
    cout << "\n***********************************************************\n";
    cout << "Number of flights out of this airport: " << controller.numberOfFlightsOutAirport(code) << "\n";
    cout << "Number of airlines that flight out of this airport: " << airlines.size() << "\n\n";
    for(const Airline& air: airlines){
        cout << " - " << air.getCode() << ";\t" << air.getName() << " - " << air.getCountry() << "\n";
    }
    printFooterOption();
}

/**
 * @brief Displays the number of flights per city or airline, depending on user input.
 */
void StatisticsMenu::flightsPerCityAirline() {
    int option;
    StatisticsController controller;
    cout << "Choose an option:\n";
    cout << "1) Airline \n";
    cout << "2) City \n";
    cout << "Option: ";
    do{
        cin >> option;
        switch(option) {
            case 1: {
                string code;
                cout << "Enter airline code: ";
                cin >> code;
                cout << "\n***********************************************************\n";
                cout << "\n - Number of flights made by this airline: " << controller.numberOfFlightsPerAirline(code) << "\n";
                break;
            }
            case 2: {
                string name;
                cout << "Enter the name of the city: ";
                cin >> name;
                cout << "\n***********************************************************\n";
                cout << "\n - Number of flights in this city: " << controller.numberOfFlightsPerCity(name) << "\n";
                break;
            }
            default: cout << "Invalid option, please try again: ";
        }
    } while(option != 1 && option != 2);
    printFooterOption();
}

/**
 * @brief Displays the number of flights per city or airline, depending on user input.
 */
void StatisticsMenu::airportToCountries() {
    int option;
    StatisticsController controller;
    cout << "Choose an option:\n";
    cout << "1) Airport \n";
    cout << "2) City \n";
    cout << "Option: ";
    do{
        cin >> option;
        switch(option) {
            case 1: {
                string code;
                cout << "Enter airport code: ";
                cin >> code;
                set<string> countries = controller.countriesForThisAirport(code);
                cout << "\n***********************************************************\n";
                cout << "\n Number of countries this airport flies to: " << countries.size() << "\n\n";
                for(const string& c: countries){
                    cout << " - " << c << "\n";
                }
                break;
            }
            case 2: {
                string name;
                cout << "Enter the name of the city: ";
                cin >> name;
                set<string> countries = controller.countriesForThisCity(name);
                cout << "\n***********************************************************\n";
                cout << "\n Number of countries this city flies to: " << countries.size() << "\n\n";
                for(const string& c: countries){
                    cout << " - " << c << "\n";
                }
                break;
            }
            default: cout << "Invalid option, please try again: ";
        }
    } while(option != 1 && option != 2);
    printFooterOption();
}

/**
 * @brief Displays the number of destinations available for a given airport.
 */
void StatisticsMenu::numberDestinations() {
    StatisticsController controller;
    string code;
    cout << "For which airport are you inquiring about the number of destinations available?\n"
              << "Enter airport code:";
    cin >> code;
    int option;
    cout << "Choose an option:\n"
              << "1) Airports \n"
              << "2) Countries \n"
              << "3) Cities \n"
              << "Option: ";
    do {
        cin >> option;
        switch (option) {
            case 1: {
                cout << "\n***********************************************************\n"
                          << "\n Number of airports available: " << controller.getNumberOfDestinationAirports(code) << endl;
                break;
            }
            case 2: {
                cout << "\n***********************************************************\n"
                          << "\n Number of countries available: " << controller.getNumberOfDestinationCountries(code) << endl;
                break;
            }
            case 3: {
                cout << "\n***********************************************************\n"
                          << "\n Number of cities available: " << controller.getNumberOfDestinationCities(code) << endl;
                break;
            }
            default: cout << "Invalid option, please try again: ";
        }
    } while (option != 1 && option != 2 && option != 3);
    printFooterOption();
}

/**
 * @brief Displays the number of reachable destinations from a given airport in a maximum number of X stops (lay-overs).
 */
void StatisticsMenu::numberDestinationXstops() {
    StatisticsController controller;
    string code;
    cout << "For which airport are you inquiring about the number of destinations available?\n"
              << "Enter airport code:";
    cin >> code;
    int stops;
    cout << "How many stops? ";
    cin >> stops;
    int option;
    cout << "Choose an option:\n"
              << "1) Airports \n"
              << "2) Countries \n"
              << "3) Cities \n"
              << "Option: ";
    do {
        cin >> option;
        switch (option) {
            case 1: {
                cout << "\n***********************************************************\n"
                          << "\n Number of airports available: " << controller.getNumberOfReachableAirportsWithMaxStops(code, stops) << endl;
                break;
            }
            case 2: {
                cout << "\n***********************************************************\n"
                          << "\n Number of countries available: " << controller.getNumberOfReachableCountriesWithMaxStops(code, stops) << endl;
                break;
            }
            case 3: {
                cout << "\n***********************************************************\n"
                          << "\n Number of cities available: " << controller.getNumberOfReachableCitiesWithMaxStops(code, stops) << endl;
                break;
            }
            default: cout << "Invalid option, please try again: ";
        }
    } while (option != 1 && option != 2 && option != 3);
    printFooterOption();
}

/**
 * @brief Displays pairs of airports representing maximum-stop trips.
 */
void StatisticsMenu::maxTrip() {
    Dataset* dataset = Dataset::getInstance();
    StatisticsController controller;
    string code;
    cout << "Enter airport code: ";
    cin >> code;
    Airport origin = dataset->findAirportByCode(code);
    vector<Airport> longestTrip = controller.getMaximumTrips(origin);
    cout << "\n***********************************************************\n";
    cout << "\n Number of stops in the longest trip: " << longestTrip.size() - 1 << endl;
    cout << "\n The longest trip: \n";
    for (const auto& airport : longestTrip) {
        cout << " -> " << airport.getAirportName() << " (" << airport.getCity() << ")" << "\n";
    }
    printFooterOption();
}

/**
 * @brief Displays the airports with the greatest air traffic capacity.
 */
void StatisticsMenu::topKAirports() {
    int k;
    StatisticsController controller;
    cout << "Enter the top numbers of airports you want to see: ";
    cin >> k;
    vector<pair<Airport, unsigned long>> airports = controller.topKAirTraffic(k);
    cout << "\n***********************************************************\n";
    cout << "\n\tTop-" << k << " Airports with Greatest Air Traffic Capacity\n\n";
    for(int i = 0; i < k && i < airports.size(); i++){
        cout << "\t" << i+1 << "° - " << airports[i].first.getAirportName() << ": " << airports[i].second << "\n";
    }
    printFooterOption();
}

/**
 * @brief Displays the airports that are essential to the network's capability.
 */
void StatisticsMenu::essentialAirports() {
    StatisticsController statisticsController;
    unordered_set<Airport> essentialAirports = statisticsController.findEssentialAirports();
    cout << "\n***********************************************************\n";
    cout << "\n Number of essential airports: " << essentialAirports.size() << endl;
    cout << endl;
    for(const Airport& a: essentialAirports){
        cout << " - " << a.getAirportCode() << ";\t" << a.getAirportName() << " - " << a.getCity() << endl;
    }
    printFooterOption();
}

/**
 * @brief Navigates back to the main menu.
 */
void StatisticsMenu::backToMain() {
    MainMenu mainMenu;
    mainMenu.display();
}

/**
 * @brief Displays the footer option and handles user input.
 */
void StatisticsMenu::printFooterOption(){
    int option;
    cout << "\n                                                   0) Back   "
              << "\n***********************************************************\n"
              << "Option: ";
    while(!(cin >> option) || option != 0) {
        cin.clear(); // clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the invalid input
        cout << "Invalid option, please try again: ";
    }
    this->display();
}