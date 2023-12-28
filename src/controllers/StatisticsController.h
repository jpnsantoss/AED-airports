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

    size_t getTotalAirports() const;

    size_t getTotalFlights() const;

    size_t getNumberOfDestinationAirports(const Airport &airport) const;

    size_t getNumberOfDestinationCountries(const Airport &airport) const;

    size_t getNumberOfDestinationCities(const Airport &airport) const;

    int getNumberOfReachableAirportsWithMaxStops(const Airport &airport, int maxStops) const;

    size_t getNumberOfReachableCountriesWithMaxStops(const Airport &airport, int maxStops) const;

    size_t getNumberOfReachableCitiesWithMaxStops(const Airport &airport, int maxStops) const;
};

#endif //PROJECT_AED_AIRPORTS_STATISTICSCONTROLLER_H
