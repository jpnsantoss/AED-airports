
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>
#include "FlightController.h"

// Method to find an airport by its code or name
Airport FlightController::findAirport(const string &identifier) {
    Dataset* dataset = Dataset::getInstance();
    try {
        // Try to find the airport by its code
        return dataset->findAirportByCode(identifier);
    } catch (runtime_error &e) {
        // If the airport is not found by its code, search all airports by their name
        const vector<Airport> &airports = dataset->getAirports();
        for (const auto &airport : airports) {
            if (airport.getAirportName() == identifier) {
                return airport;
            }
        }
    }

    throw runtime_error("Airport not found");
}

vector<Airport> FlightController::findAirportsByName(const string &name) {
    Dataset* dataset = Dataset::getInstance();
    const vector<Airport> &airports = dataset->getAirports();
    vector<Airport> matchingAirports;

    for (const auto &airport : airports) {
        if (airport.getAirportName() == name) {
            matchingAirports.push_back(airport);
        }
    }

    return matchingAirports;
}

// Method to find all airports in a given city
vector<Airport> FlightController::findAirportsByCity(const string &city) {
    Dataset* dataset = Dataset::getInstance();
    const vector<Airport> &airports = dataset->getAirports();
    vector<Airport> airportsInCity;

    for (const auto &airport : airports) {
        if (airport.getCity() == city) {
            airportsInCity.push_back(airport);
        }
    }

    return airportsInCity;
}


vector<Airport> FlightController::getNearestAirports(const Location &location) {
    Dataset* dataset = Dataset::getInstance();
    const vector<Airport> &airports = dataset->getAirports();
    vector<Airport> nearestAirports;
    double minDistance = numeric_limits<double>::max();

    for (const auto &airport : airports) {
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

