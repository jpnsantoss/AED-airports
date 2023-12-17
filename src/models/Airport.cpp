//
// Created by jpsantos on 16-12-2023.
//

#include "Airport.h"

// Constructor
Airport::Airport(const string &airportCode, const string &airportName, const string &city, const string &country)
        : airportCode(airportCode), airportName(airportName), city(city), country(country) {}

// Getters
string Airport::getAirportCode() const {
    return airportCode;
}

string Airport::getAirportName() const {
    return airportName;
}

string Airport::getCity() const {
    return city;
}

string Airport::getCountry() const {
    return country;
}

// Setters
void Airport::setAirportCode(const string &airportCode) {
    Airport::airportCode = airportCode;
}

void Airport::setAirportName(const string &airportName) {
    Airport::airportName = airportName;
}

void Airport::setCity(const string &city) {
    Airport::city = city;
}

void Airport::setCountry(const string &country) {
    Airport::country = country;
}