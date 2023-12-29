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

    size_t getNumberOfDestinationAirports(const string& code) const;

    size_t getNumberOfDestinationCountries(const string& code) const;

    size_t getNumberOfDestinationCities(const string& code) const;

    int getNumberOfReachableAirportsWithMaxStops(const string& code, int maxStops) const;

    size_t getNumberOfReachableCountriesWithMaxStops(const string& code, int maxStops) const;

    size_t getNumberOfReachableCitiesWithMaxStops(const string& code, int maxStops) const;

    static set<string> numberOfCountriesForThisAirport(string &identifier);

    static int numberOfFlightsPerAirline(string &identifier);

    static int numberOfFlightsPerCity(string &identifier);

    static set<Airline> setOfFlightsOutAirport(string &identifier);

    static int numberOfFlightsOutAirport(string &identifier);

    static set<string> numberOfCountriesForThisCity(string &identifier);

    vector<pair<Airport, Airport>> getMaximumTrips();
};

#endif //PROJECT_AED_AIRPORTS_STATISTICSCONTROLLER_H
