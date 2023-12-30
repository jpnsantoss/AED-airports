#ifndef PROJECT_AED_AIRPORTS_STATISTICSCONTROLLER_H
#define PROJECT_AED_AIRPORTS_STATISTICSCONTROLLER_H

#include <iostream>
#include <set>
#include "models/Airport.h"
#include "utils/Dataset.h"
using namespace std;

class StatisticsController {
private:
    Graph<Airport> airportGraph;

public:
    StatisticsController();

    static size_t getTotalAirports() ;

    static size_t getTotalFlights() ;

    size_t getNumberOfDestinationAirports(const Airport &airport) const;

    size_t getNumberOfDestinationCountries(const Airport &airport) const;

    size_t getNumberOfDestinationCities(const Airport &airport) const;

    int getNumberOfReachableAirportsWithMaxStops(const Airport &airport, int maxStops) const;

    size_t getNumberOfReachableCountriesWithMaxStops(const Airport &airport, int maxStops) const;

    size_t getNumberOfReachableCitiesWithMaxStops(const Airport &airport, int maxStops) const;

    static set<string> numberOfCountriesForThisAirport(string &identifier);

    static int numberOfFlightsPerAirline(string &identifier);

    static int numberOfFlightsPerCity(string &identifier);

    static set<Airline> setOfFlightsOutAirport(string &identifier);

    static int numberOfFlightsOutAirport(string &identifier);

    static set<string> numberOfCountriesForThisCity(string &identifier);

    vector<pair<Airport, Airport>> getMaximumTrips();

    unordered_set<Airport> findEssentialAirports();

    void dfsForEssentialAirports(Vertex<Airport> *vertex, unordered_set<Airport> &essentialAirports,
                                 stack<Vertex<Airport> *> &vertexStack, int &index);
};

#endif //PROJECT_AED_AIRPORTS_STATISTICSCONTROLLER_H
