
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include "FlightController.h"

// Method to find an airport by its code or name
/**
 * @brief Finds an airport by its code.
 * Complexity: O(n), where n is the number of airports in the dataset.
 * @param identifier - the code of the airport to find.
 * @return The found airport.
 */
Airport FlightController::findAirport(const string &identifier) {
    Dataset* dataset = Dataset::getInstance();
    try {
        // Try to find the airport by its code
        return dataset->findAirportByCode(identifier);
    } catch (runtime_error &e) {
        // If the airport is not found by its code, search all airports by their name
        const vector<Airport> &airports = dataset->getAirports();
        for (const Airport& airport : airports) {
            if (airport.getAirportCode() == identifier) {
                return airport;
            }
        }
    }

    throw runtime_error("Airport not found");
}

/**
 * @brief Finds all airports with a given name.
 * Complexity: O(n), where n is the number of airports in the dataset.
 * @param name - the name of the airports to find.
 * @return A vector containing all the airports found.
 */
vector<Airport> FlightController::findAirportsByName(const string &name) {
    Dataset* dataset = Dataset::getInstance();
    const vector<Airport> &airports = dataset->getAirports();
    vector<Airport> matchingAirports;

    for (const Airport& airport : airports) {
        if (airport.getAirportName() == name) {
            matchingAirports.push_back(airport);
        }
    }

    return matchingAirports;
}

// Method to find all airports in a given city
/**
 * @brief Finds all airports in a given city.
 * Complexity: O(n), where n is the number of airports in the dataset.
 * @param city - the name of the city to find.
 * @return A vector containing all the airports found.
 */
vector<Airport> FlightController::findAirportsByCity(const string &city) {
    Dataset* dataset = Dataset::getInstance();
    const vector<Airport> &airports = dataset->getAirports();
    vector<Airport> airportsInCity;

    for (const Airport& airport : airports) {
        if (airport.getCity() == city) {
            airportsInCity.push_back(airport);
        }
    }

    return airportsInCity;
}

/**
 * @brief Gets the nearest airports to a given location.
 * Complexity: O(n), where n is the number of airports in the dataset.
 * @param location - the location to find the nearest airports from.
 * @return A vector containing all the airports found.
 */
vector<Airport> FlightController::getNearestAirports(const Location &location) {
    Dataset* dataset = Dataset::getInstance();
    const vector<Airport> &airports = dataset->getAirports();
    vector<Airport> nearestAirports;
    double minDistance = numeric_limits<double>::max();

    for (const Airport& airport : airports) {
        double distance = location.calculateDistanceTo(airport.getLocation());
        if (distance < minDistance) {
            nearestAirports.clear();
            minDistance = distance;
        }
        if (distance == minDistance) {
            nearestAirports.push_back(airport);
        }
    }

    return nearestAirports;
}

