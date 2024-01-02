
#ifndef PROJECT_AED_AIRPORTS_FLIGHTCONTROLLER_H
#define PROJECT_AED_AIRPORTS_FLIGHTCONTROLLER_H

#include <vector>
#include <set>
#include "utils/Dataset.h"
#include "models/Airport.h"

using namespace std;

class FlightController {

public:
    static unordered_set<Airport> findAirportsByName(const string &name);
    static unordered_set<Airport> findAirportsByCity(const string &city);
    static Airport findAirport(const string &identifier);
    static unordered_set<Airport> getNearestAirports(const Location &location);
};

#endif //PROJECT_AED_AIRPORTS_FLIGHTCONTROLLER_H