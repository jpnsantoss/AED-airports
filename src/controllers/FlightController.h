//
// Created by jpsantos on 21-12-2023.
//

#ifndef PROJECT_AED_AIRPORTS_FLIGHTCONTROLLER_H
#define PROJECT_AED_AIRPORTS_FLIGHTCONTROLLER_H

#include "utils/Dataset.h"
#include "models/Airport.h"
#include <vector>

enum class FlightOption {
    ByAirportCode,
    ByAirportName,
    ByCity,
    ByLocation
};

class FlightController {

protected:
    Graph<Airport> airportGraph;
public:
    FlightController();

    vector<Airport> findAirportsByName(const string &name);
    vector<Airport> findAirportsByCity(const string &city);


    Airport findAirport(const string &identifier);

    virtual vector<vector<Airport>> getShortestPathsBFS(const Airport &origin, const Airport &destination);

    void buildPaths(Vertex<Airport> *origin, Vertex<Airport> *destination,
                    map<Vertex<Airport> *, std::vector<Vertex<Airport> *>> &prev, vector<Airport> &path,
                    vector<std::vector<Airport>> &paths);

    vector<Airport> getNearestAirports(const Location &location);

    vector<vector<Airport>>
    getBestFlightOption(FlightOption sourceOption, const string &source, FlightOption destinationOption,
                        const string &destination);

    void findBestFlightPaths(const string &source, const string &destination, vector<vector<Airport>> &res);
};

#endif //PROJECT_AED_AIRPORTS_FLIGHTCONTROLLER_H