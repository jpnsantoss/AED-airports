
#ifndef PROJECT_AED_AIRPORTS_BESTOPTIONCONTROLLER_H
#define PROJECT_AED_AIRPORTS_BESTOPTIONCONTROLLER_H

#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>
#include "utils/Dataset.h"
#include "models/Airport.h"

using namespace std;

enum class FlightOption {
    ByAirportCode,
    ByAirportName,
    ByCity,
    ByLocation,
    INVALID
};

class BestOptionController {
protected:
    Graph<Airport> airportGraph;

    virtual vector<vector<Airport>> getShortestPathsBFS(const Airport &origin, const Airport &destination);

    void buildPaths(Vertex<Airport> *origin, Vertex<Airport> *destination,
                    map<Vertex<Airport> *, vector<Vertex<Airport> *>> &prev, vector<Airport> &path,
                    vector<vector<Airport>> &paths);

    void findBestFlightPaths(const string &source, const string &destination, vector<vector<Airport>> &res);

public:
    // Constructor
    BestOptionController();

    vector<vector<Airport>>
    getBestFlightOption(FlightOption sourceOption, const string &source, FlightOption destinationOption,
                        const string &destination);
};


#endif //PROJECT_AED_AIRPORTS_BESTOPTIONCONTROLLER_H
