#ifndef PROJECT_AED_AIRPORTS_DATASET_H
#define PROJECT_AED_AIRPORTS_DATASET_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "utils/Graph.h"
#include "models/Flight.h"
#include "models/Airport.h"
#include "models/Airline.h"

using namespace std;

class Dataset {
private:
    Graph<Airport> airportGraph;

    vector<Flight> flights;
    vector<Airport> airports;
    vector<Airline> airlines;

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
    const vector<Flight> &getFlights() const;
    const vector<Airport> &getAirports() const;
    const vector<Airline> &getAirlines() const;
    const Graph<Airport>& getAirportGraph() const;

    // Find methods
    Airport findAirportByCode(const string &code);
    Airline findAirlineByCode(const string &code);
    Flight* findFlight(const Airport& source, const Airport& destination);
};

#endif //PROJECT_AED_AIRPORTS_DATASET_H