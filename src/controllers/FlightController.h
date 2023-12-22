//
// Created by jpsantos on 21-12-2023.
//

#ifndef PROJECT_AED_AIRPORTS_FLIGHTCONTROLLER_H
#define PROJECT_AED_AIRPORTS_FLIGHTCONTROLLER_H

#include "utils/Dataset.h"
#include "models/Airport.h"
#include <vector>

class FlightController {
private:
    Graph<Airport> airportGraph;

public:
    FlightController();

    vector<Airport> findAirportsByCity(const string &city);


    Airport findAirport(const string &identifier);

    vector<vector<Airport>> getShortestPathsBFS(const Airport &origin, const Airport &destination);

    vector<vector<Airport>> getBestFlightOptionByAirport(const string &source, const string &destination);

    vector<vector<Airport>> getBestFlightOptionByCity(const string &source, const string &destination);

    void buildPaths(Vertex<Airport> *origin, Vertex<Airport> *destination,
                    map<Vertex<Airport> *, std::vector<Vertex<Airport> *>> &prev, vector<Airport> &path,
                    vector<std::vector<Airport>> &paths);
};

#endif //PROJECT_AED_AIRPORTS_FLIGHTCONTROLLER_H