//
// Created by jpsantos on 16-12-2023.
//

#ifndef PROJECT_AED_AIRPORTS_AIRPORT_H
#define PROJECT_AED_AIRPORTS_AIRPORT_H

#include <string>
using namespace std;
#include "Location.h"

class Airport {
private:
    string airportCode;
    string airportName;
    string city;
    string country;
    Location location;

public:
    // Constructor
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

    bool operator == (const Airport &other) const;
    friend ostream & operator << (ostream &os, Airport &airport);
};

#endif //PROJECT_AED_AIRPORTS_AIRPORT_H
