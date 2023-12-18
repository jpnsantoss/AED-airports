//
// Created by jpsantos on 16-12-2023.
//

#include "Airport.h"

// Constructor
Airport::Airport(const string &airportCode, const string &airportName, const string &city, const string &country, const Location &location)
        : airportCode(airportCode), airportName(airportName), city(city), country(country), location(location) {}

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

Location Airport::getLocation() const {
    return location;
}

// Setters
void Airport::setAirportCode(const string &airportCode) {
    this->airportCode = airportCode;
}

void Airport::setAirportName(const string &airportName) {
    this->airportName = airportName;
}

void Airport::setCity(const string &city) {
    this->city = city;
}

void Airport::setCountry(const string &country) {
    this->country = country;
}

void Airport::setLocation(const Location &location) {
    this->location = location;
}

double Airport::calculateDistanceTo(const Airport &other) const {
    return this->location.calculateDistanceTo(other.getLocation());
}

ostream &operator<<(ostream &os, Airport &airport) {
    os << airport.getAirportCode();
    return os;
}

bool Airport::operator==(const Airport &other) const {
    return (this->airportCode == other.getAirportCode());
}
