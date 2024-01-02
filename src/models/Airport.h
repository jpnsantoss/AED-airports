
#ifndef PROJECT_AED_AIRPORTS_AIRPORT_H
#define PROJECT_AED_AIRPORTS_AIRPORT_H

#include <string>
#include "Location.h"

using namespace std;

class Airport {
private:
    string airportCode;
    string airportName;
    string city;
    string country;
    Location location;

public:
    // Constructor
    Airport();
    Airport(const string &airportCode);
    Airport(const string &airportCode, const string &airportName, const string &city, const string &country, const Location &location);

    // Getters
    string getAirportCode() const;
    string getAirportName() const;
    string getCity() const;
    string getCountry() const;
    Location getLocation() const;

    // Setters
    void setAirportCode(const string &airportCode);
    void setAirportName(const string &airportName);
    void setCity(const string &city);
    void setCountry(const string &country);
    void setLocation(const Location &location);

    // Operators
    bool operator == (const Airport &other) const;
    friend ostream & operator << (ostream &os, Airport &airport);
};

// Hash function for Airport class
template <>
struct std::hash<Airport> {
    size_t operator()(const Airport& airport) const {
        size_t airportCode = hash<string>{}(airport.getAirportCode());
        return airportCode; // Combine the hashes appropriately
    }
};

#endif //PROJECT_AED_AIRPORTS_AIRPORT_H
