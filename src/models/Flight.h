
#ifndef PROJECT_AED_AIRPORTS_FLIGHT_H
#define PROJECT_AED_AIRPORTS_FLIGHT_H

#include <string>
#include "Airport.h"
#include "Airline.h"

using namespace std;

class Flight {
private:
    Airport source;
    Airport target;
    Airline airline;
    double distance;

public:
    // Constructor
    Flight(const Airport &source, const Airport &target, const Airline &airline);

    // Getters
    Airport getSource() const;
    Airport getTarget() const;
    Airline getAirline() const;
    double getDistance() const;

    // Setters
    void setSource(const Airport &source);
    void setTarget(const Airport &target);
    void setAirline(const Airline &airline);
};
#endif //PROJECT_AED_AIRPORTS_FLIGHT_H