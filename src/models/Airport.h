//
// Created by jpsantos on 16-12-2023.
//

#ifndef PROJECT_AED_AIRPORTS_AIRPORT_H
#define PROJECT_AED_AIRPORTS_AIRPORT_H

#include <string>
using namespace std;
class Airport {
private:
    string airportCode;
    string airportName;
    string city;
    string country;

public:
    // Constructor
    Airport(const string &airportCode, const string &airportName, const string &city, const string &country);

    // Getters
    string getAirportCode() const;
    string getAirportName() const;
    string getCity() const;
    string getCountry() const;

    // Setters
    void setAirportCode(const string &airportCode);
    void setAirportName(const string &airportName);
    void setCity(const string &city);
    void setCountry(const string &country);
};

#endif //PROJECT_AED_AIRPORTS_AIRPORT_H
