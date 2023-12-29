
#ifndef PROJECT_AED_AIRPORTS_BESTOPTIONCONTROLLER_H
#define PROJECT_AED_AIRPORTS_BESTOPTIONCONTROLLER_H

#include "utils/Dataset.h"
#include "models/Airport.h"
#include <vector>
#include <set>

enum class FlightOption {
    ByAirportCode,
    ByAirportName,
    ByCity,
    ByLocation
};

class BestOptionController {
protected:
    Graph<Airport> airportGraph;

    virtual vector<vector<Airport>> getShortestPathsBFS(const Airport &origin, const Airport &destination);

    void buildPaths(Vertex<Airport> *origin, Vertex<Airport> *destination,
                    map<Vertex<Airport> *, std::vector<Vertex<Airport> *>> &prev, vector<Airport> &path,
                    vector<std::vector<Airport>> &paths);

    void findBestFlightPaths(const string &source, const string &destination, vector<vector<Airport>> &res);

public:
    BestOptionController();
    vector<vector<Airport>>
    getBestFlightOption(FlightOption sourceOption, const string &source, FlightOption destinationOption,
                        const string &destination);
};


#endif //PROJECT_AED_AIRPORTS_BESTOPTIONCONTROLLER_H
