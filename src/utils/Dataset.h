#ifndef PROJECT_AED_AIRPORTS_DATASET_H
#define PROJECT_AED_AIRPORTS_DATASET_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_set>
#include "utils/Graph.h"
#include "models/Flight.h"
#include "models/Airport.h"
#include "models/Airline.h"

using namespace std;

class Dataset {
private:
    Graph<Airport> airportGraph;

    unordered_set<Flight> flights;
    unordered_set<Airport> airports;
    unordered_set<Airline> airlines;

    static Dataset* dataset;
    // Private constructor so that no objects can be created.
    Dataset();

    // Load data methods
    void loadFlights();
    void loadAirports();
    void loadAirlines();

public:
    // Static access method
    static Dataset* getInstance();

    // Delete copy constructor and assignment operator
    Dataset(const Dataset&) = delete;
    void operator=(const Dataset&) = delete;

    // Getters
    const unordered_set<Flight> &getFlights() const;
    const unordered_set<Airport> &getAirports() const;
    const unordered_set<Airline> &getAirlines() const;
    const Graph<Airport>& getAirportGraph() const;

    // Find methods
    Airport findAirportByCode(const string &code);
    Airline findAirlineByCode(const string &code);
    Flight * findFlight(const Airport &source, const Airport &destination);

    Airport findAirport(const string &code);
};

#endif //PROJECT_AED_AIRPORTS_DATASET_H