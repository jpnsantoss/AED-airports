#ifndef PROJECT_AED_AIRPORTS_DATASET_H
#define PROJECT_AED_AIRPORTS_DATASET_H

#include <vector>
#include <string>
#include "models/Flight.h"
#include "models/Airport.h"
#include "models/Airline.h"

class Dataset {
private:
    std::vector<Flight> flights;
    std::vector<Airport> airports;
    std::vector<Airline> airlines;

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
    const std::vector<Flight> &getFlights() const;
    const std::vector<Airport> &getAirports() const;
    const std::vector<Airline> &getAirlines() const;
};

#endif //PROJECT_AED_AIRPORTS_DATASET_H