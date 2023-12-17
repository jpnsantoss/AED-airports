//
// Created by jpsantos on 16-12-2023.
//

#include "Airline.h"

// Constructor
Airline::Airline(const string &airlineCode, const string &airlineName)
        : airlineCode(airlineCode), airlineName(airlineName) {}

// Getters
string Airline::getAirlineCode() const {
    return airlineCode;
}

string Airline::getAirlineName() const {
    return airlineName;
}

// Setters
void Airline::setAirlineCode(const string &airlineCode) {
    this->airlineCode = airlineCode;
}

void Airline::setAirlineName(const string &airlineName) {
    this->airlineName = airlineName;
}