
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

    bool operator==(const Flight& other) const {
        return source == other.source && target == other.target && airline == other.airline;
    }
};

namespace std {
    template <>
    struct hash<Flight> {
        size_t operator()(const Flight& flight) const {
            // Compute individual hash values for three data members and combine them using XOR and bit shifting
            return ((hash<Airport>()(flight.getSource())
                     ^ (hash<Airport>()(flight.getTarget()) << 1)) >> 1)
                   ^ (hash<Airline>()(flight.getAirline()) << 1);
        }
    };
}

#endif //PROJECT_AED_AIRPORTS_FLIGHT_H