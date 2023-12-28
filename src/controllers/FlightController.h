//
// Created by jpsantos on 21-12-2023.
//

#ifndef PROJECT_AED_AIRPORTS_FLIGHTCONTROLLER_H
#define PROJECT_AED_AIRPORTS_FLIGHTCONTROLLER_H

#include "utils/Dataset.h"
#include "models/Airport.h"
#include <vector>
#include <set>



class FlightController {

public:
    static vector<Airport> findAirportsByName(const string &name);
    static vector<Airport> findAirportsByCity(const string &city);
    static Airport findAirport(const string &identifier);
    static vector<Airport> getNearestAirports(const Location &location);
};

#endif //PROJECT_AED_AIRPORTS_FLIGHTCONTROLLER_H