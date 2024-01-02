#include "FlightController.h"

// Method to find an airport by its code or name

/**
 * @brief Finds an airport by its code or name.
 * Complexity: O(1) if the airport is found by code, O(n) otherwise, where n is the number of airports in the dataset.
 * @param code - the code or name of the airport to find.
 * @return The airport found.
 */
Airport FlightController::findAirport(const string &code) {
    Dataset* dataset = Dataset::getInstance();
    const unordered_set<Airport>& airports = dataset->getAirports();
    auto it = airports.find(Airport(code));
    if (it != airports.end()) {
        return *it;
    }
    throw runtime_error("Airport not found");
}

/**
 * @brief Finds all airports with a given name.
 * Complexity: O(n), where n is the number of airports in the dataset.
 * @param name - the name of the airports to find.
 * @return A vector containing all the airports found.
 */
unordered_set<Airport> FlightController::findAirportsByName(const string &name) {
    Dataset* dataset = Dataset::getInstance();
    const unordered_set<Airport>& airports = dataset->getAirports();
    unordered_set<Airport> matchingAirports;

    for (const Airport& airport : airports) {
        if (airport.getAirportName() == name) {
            matchingAirports.insert(airport);
        }
    }

    return matchingAirports;
}

/**
 * @brief Finds all airports in a given city.
 * Complexity: O(n), where n is the number of airports in the dataset.
 * @param city - the name of the city to find.
 * @return An unordered_set containing all the airports found.
 */
unordered_set<Airport> FlightController::findAirportsByCity(const string &city) {
    Dataset* dataset = Dataset::getInstance();
    const unordered_set<Airport>& airports = dataset->getAirports();
    unordered_set<Airport> airportsInCity;

    for (const Airport& airport : airports) {
        if (airport.getCity() == city) {
            airportsInCity.insert(airport);
        }
    }

    return airportsInCity;
}

/**
 * @brief Gets the nearest airports to a given location.
 * Complexity: O(n), where n is the number of airports in the dataset.
 * @param location - the location to find the nearest airports from.
 * @return An unordered_set containing all the nearest airports.
 */
unordered_set<Airport> FlightController::getNearestAirports(const Location &location) {
    Dataset* dataset = Dataset::getInstance();
    const unordered_set<Airport>& airports = dataset->getAirports();
    unordered_set<Airport> nearestAirports;
    double minDistance = numeric_limits<double>::max();

    for (const Airport& airport : airports) {
        double distance = location.calculateDistanceTo(airport.getLocation());
        if (distance < minDistance) {
            nearestAirports.clear();
            minDistance = distance;
        }
        if (distance == minDistance) {
            nearestAirports.insert(airport);
        }
    }

    return nearestAirports;
}
